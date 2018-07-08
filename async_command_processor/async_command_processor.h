// command_processor.h in Otus homework#11 project

#pragma once

#include <memory>
#include <mutex>
#include <list>
#include <thread>
#include <functional>
#include <cstdlib>
#include <condition_variable>
#include "command_processor_instance.h"

using namespace std::chrono_literals;


template <size_t loggingThreadCount = 2u>
class AsyncCommandProcessor : public std::enable_shared_from_this<AsyncCommandProcessor<loggingThreadCount>>,
                              public MessageBroadcaster
{
public:

  AsyncCommandProcessor(      
      const size_t newBulkSize = 3,
      const char newBulkOpenDelimiter = '{',
      const char newBulkCloseDelimiter = '}',
      std::ostream& newOutputStream = std::cout,
      std::ostream& newErrorStream = std::cerr,
      std::ostream& newMetricsStream = std::cout
  ) :    
    sharedThis{},
    accessLock{},
    disconnected{false}, receiving{false},
    terminationNotifier{}, activeReceptionCount{},

    bulkSize{newBulkSize},
    bulkOpenDelimiter{newBulkOpenDelimiter},
    bulkCloseDelimiter{newBulkCloseDelimiter},
    outputStream{newOutputStream},
    errorStream{newErrorStream},
    metricsStream{newMetricsStream},

    processor{
      std::make_shared<CommandProcessorInstance<loggingThreadCount>>(
        bulkSize,
        bulkOpenDelimiter,
        bulkCloseDelimiter,
        outputStream,
        errorStream,
        metricsStream,
        screenOutputLock
      )
    },

    entryPoint{processor->getEntryPoint()},
    commandBuffer{processor->getInputBuffer()},
    bulkBuffer{processor->getOutputBuffer()},
    metrics{processor->getMetrics()},
    selfDestroy{}
  {
    this->addMessageListener(entryPoint);
  }

  ~AsyncCommandProcessor()
  {
    #ifdef NDEBUG
    #else
        std::cout << "\n                            AsyncCP destructor\n";
    #endif

//    if (selfDestroy.joinable())
//    {
//      selfDestroy.join();
//    }
  }

  bool connect(const bool outputMetrics = false) noexcept
  {
    try
    {
      /* ignore repetitive connection attempts*/
      if (workingThread.joinable() == true)
      {
        return false;
      }

//      if (nullptr == sharedThis)
//      {
//         sharedThis = this->shared_from_this();
//      }

      #ifdef NDEBUG
      #else
        //std::cout << "\n                    AsyncCP working thread start\n";
      #endif      

      workingThread = std::thread{
          &AsyncCommandProcessor<loggingThreadCount>::run, this, outputMetrics
      };

      #ifdef NDEBUG
      #else
        //std::cout << "\n                    AsyncCP connected\n";
      #endif

      return true;
    }
    catch (const std::exception& ex)
    {
      std::lock_guard<std::mutex> lockOutput{screenOutputLock};

      errorStream << "Connection failed. Reason: " << ex.what() << std::endl;
      return false;
    }
  }

  void run(const bool outputMetrics = false)
  {
     processor->run();

     if (outputMetrics != true)
     {
       return;
     }

     /* Output metrics */
     std::lock_guard<std::mutex> lockOutput{screenOutputLock};

     metricsStream << "total received - "
                   << metrics["input reader"]->totalReceptionCount << " data chunk(s), "
                   << metrics["input reader"]->totalCharacterCount << " character(s), "
                   << metrics["input reader"]->totalStringCount << " string(s)" << std::endl
                   << "total processed - "
                   << metrics["input processor"]->totalStringCount << " string(s), "
                   << metrics["input processor"]->totalCommandCount << " command(s), "
                   << metrics["input processor"]->totalBulkCount << " bulk(s)" << std::endl
                   << "total displayed - "
                   << metrics["publisher"]->totalBulkCount << " bulk(s), "
                   << metrics["publisher"]->totalCommandCount << " command(s)" << std::endl;

     for (size_t threadIndex{}; threadIndex < loggingThreadCount; ++threadIndex)
     {
       auto threadName = std::string{"logger thread#"} + std::to_string(threadIndex);
       metricsStream << "total saved by thread #" << threadIndex << " - "
                     << metrics[threadName]->totalBulkCount << " bulk(s), "
                     << metrics[threadName]->totalCommandCount << " command(s)" << std::endl;

     }
     metricsStream << std::endl;
  }

  void receiveData(const char *data, std::size_t size)
  {
    if (nullptr == data || size == 0 || disconnected.load() == true)
    {
      #ifdef NDEBUG
      #else
//        std::lock_guard<std::mutex> lockScreenOutput{screenOutputLock};
//          std::cout << "                                stop receiving\n";
      #endif

      receiving.store(false);

//      lockAccess.unlock();

//      --activeReceptionCount;

//      terminationNotifier.notify_all();

      return;
    }

    ++activeReceptionCount;

    std::cout << "                                activeReceptionCount at receive:" << activeReceptionCount.load() << "\n";

    std::unique_lock<std::mutex> lockAccess{accessLock};
    receiving.store(true);

    lockAccess.unlock();

    {
       #ifdef NDEBUG
       #else
//         std::lock_guard<std::mutex> lockScreenOutput{screenOutputLock};
//         std::cout << "                                receiving started\n";
       #endif
    }


    if (entryPoint != nullptr && disconnected.load() != true)
    {
      InputReader::EntryDataType newData{};
      for (size_t idx{0}; idx < size; ++idx)
      {
        newData.push_back(data[idx]);
      }

      entryPoint->putItem(std::move(newData));
    }

    {
      #ifdef NDEBUG
      #else
//        std::lock_guard<std::mutex> lockScreenOutput{screenOutputLock};
//        std::cout << "                                receiving finished\n";
      #endif
    }


   receiving.store(false);

   --activeReceptionCount;

   terminationNotifier.notify_all();
  }

  void disconnect()
  {
    std::unique_lock<std::mutex> lockAccess{accessLock};
    disconnected.store(true);

    {
      #ifdef NDEBUG
      #else
//        std::lock_guard<std::mutex> lockScreenOutput{screenOutputLock};
//        std::cout << "                                disconnect started\n";
      #endif
    }

    sendMessage(Message::NoMoreData);

    lockAccess.unlock();


    {
      #ifdef NDEBUG
      #else
//        std::lock_guard<std::mutex> lockScreenOutput{screenOutputLock};
//        std::cout << "                                disconnect finished\n";
      #endif
    }

    //std::this_thread::sleep_for(250ms);

    std::unique_lock<std::mutex> lockTermination{terminationLock};

    while (activeReceptionCount.load() != 0)
    {
      #ifdef NDEBUG
      #else
        std::cout << "\n                    AsyncCP waiting active receptions termination\n";
      #endif

      terminationNotifier.wait_for(lockTermination, 100ms, [this]()
      {
        return activeReceptionCount.load() == 0;
      }
      );
    }

    std::cout << "                                activeReceptionCount after disconnect:" << activeReceptionCount.load() << "\n";

    lockTermination.unlock();

    #ifdef NDEBUG
    #else
      //std::cout << "\n                    AsyncCP finishing\n";
    #endif

    if (workingThread.joinable() == true)
    {
      workingThread.join();
    }



//    selfDestroy = std::thread(
//      [this]()
//      {
//        try
//        {
//          std::this_thread::sleep_for(1500ms);
//          sharedThis.reset();
//        }
//        catch (const std::exception& ex)
//        {
//           std::cerr << ex.what() << std::endl;
//        }
//      }
//    );

//    sharedThis.reset();

    #ifdef NDEBUG
    #else
      //std::cout << "\n                    AsyncCP disconnect\n";
    #endif
  }

  bool isDisconnected()
  {
    return disconnected.load();
  }

  const std::shared_ptr<InputProcessor::InputBufferType>&
  getCommandBuffer() const
  { return commandBuffer; }


  const std::shared_ptr<InputProcessor::OutputBufferType>&
  getBulkBuffer() const
  { return bulkBuffer; }

  const SharedGlobalMetrics getMetrics()
  {
    return metrics;
  }

  std::mutex& getScreenOutputLock()
  { return screenOutputLock;}

private:

  static std::mutex screenOutputLock;

  std::shared_ptr<AsyncCommandProcessor<loggingThreadCount>> sharedThis;

  std::mutex accessLock;  
  std::atomic<bool> disconnected;
  std::atomic<bool> receiving;

  std::mutex terminationLock;
  std::atomic<size_t> activeReceptionCount;
  std::condition_variable terminationNotifier;


  const size_t bulkSize;
  const char bulkOpenDelimiter;
  const char bulkCloseDelimiter;
  std::ostream& outputStream;
  std::ostream& errorStream;
  std::ostream& metricsStream;

  std::shared_ptr<CommandProcessorInstance<loggingThreadCount>> processor;

  std::shared_ptr<InputReader::InputBufferType> entryPoint{nullptr};
  std::shared_ptr<InputProcessor::InputBufferType> commandBuffer;
  std::shared_ptr<InputProcessor::OutputBufferType> bulkBuffer;  

  std::thread workingThread;

  SharedGlobalMetrics metrics;

  std::size_t timeStampID;

  std::thread selfDestroy;
};

template <size_t loggingThreadCount>
std::mutex AsyncCommandProcessor<loggingThreadCount>::screenOutputLock{};
