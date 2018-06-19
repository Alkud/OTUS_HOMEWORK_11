// command_processor.h in Otus homework#11 project

#pragma once

#include <memory>
#include <mutex>
#include <list>
#include <thread>
#include <functional>
#include <condition_variable>
#include "command_processor_instance.h"

template <size_t loggingThreadsCount = 2u>
class AsyncCommandProcessor : public MessageBroadcaster
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
    bulkSize{newBulkSize},
    bulkOpenDelimiter{newBulkOpenDelimiter},
    bulkCloseDelimiter{newBulkCloseDelimiter},
    outputStream{newOutputStream},
    errorStream{newErrorStream},
    metricsStream{newMetricsStream},
    processor{nullptr}, entryPoint{nullptr},
    commandBuffer{nullptr}, bulkBuffer{nullptr},
    metrics{}
  {}

  ~AsyncCommandProcessor()
  {
    if (workingThread.joinable() == true)
    {
      workingThread.join();
    }
  }

  bool connect() noexcept
  {
    try
    {
      /* ignore repetitive connection attempts*/
      if (processor != nullptr || workingThread.joinable() == true)
      {
        return false;
      }

      processor = std::make_shared<CommandProcessorInstance<loggingThreadsCount>>(
        bulkSize,
        bulkOpenDelimiter,
        bulkCloseDelimiter,
        outputStream,
        errorStream,
        metricsStream
      );

      entryPoint = processor->getEntryPoint();
      commandBuffer = processor->getInputBuffer();
      bulkBuffer = processor->getOutputBuffer();
      this->addMessageListener(entryPoint);


      #ifdef NDEBUG
      #else
        std::cout << "\n                    AsyncCP working thread start\n";
      #endif

      workingThread = std::thread{
          &AsyncCommandProcessor<loggingThreadsCount>::run, this, true
      };

      #ifdef NDEBUG
      #else
        std::cout << "\n                    AsyncCP connected\n";
      #endif

      return true;
    }
    catch (const std::exception& ex)
    {
      std::cerr << "Connection failed. Reason: " << ex.what() << std::endl;
      return false;
    }
  }

  void run(const bool outputMetrics = false)
  {
     auto globalMetrics {processor->run()};

     metrics = globalMetrics;

     if (outputMetrics != true)
     {
       return;
     }

     /* Output metrics */
     metricsStream << "total received - "
                   << globalMetrics["input reader"]->totalReceptionCount << " data chunk(s), "
                   << globalMetrics["input reader"]->totalCharacterCount << " character(s), "
                   << globalMetrics["input reader"]->totalStringCount << " string(s)" << std::endl
                   << "total processed - "
                   << globalMetrics["input processor"]->totalStringCount << " string(s), "
                   << globalMetrics["input processor"]->totalCommandCount << " command(s), "
                   << globalMetrics["input processor"]->totalBulkCount << " bulk(s)" << std::endl
                   << "total displayed - "
                   << globalMetrics["publisher"]->totalBulkCount << " bulk(s), "
                   << globalMetrics["publisher"]->totalCommandCount << " command(s)" << std::endl;

     for (size_t threadIndex{}; threadIndex < loggingThreadsCount; ++threadIndex)
     {
       auto threadName = std::string{"logger thread#"} + std::to_string(threadIndex);
       metricsStream << "total saved by thread #" << threadIndex << " - "
                     << globalMetrics[threadName]->totalBulkCount << " bulk(s), "
                     << globalMetrics[threadName]->totalCommandCount << " command(s)" << std::endl;
     }
  }

  void receiveData(const char *data, std::size_t size) const
  {
    if (nullptr == data || size == 0)
    {
      return;
    }

    if (entryPoint != nullptr)
    {
      InputReader::EntryDataType newData{};
      for (size_t idx{0}; idx < size; ++idx)
      {
        newData.push_back(data[idx]);
      }
      std::lock_guard<std::mutex> lockExternalBuffer{entryPoint->dataLock};
      entryPoint->putItem(std::move(newData));
    }

    #ifdef NDEBUG
    #else
      std::cout << "\n                    AsyncCP received data\n";
    #endif
  }

  void disconnect()
  {
    sendMessage(Message::NoMoreData);

    #ifdef NDEBUG
    #else
      std::cout << "\n                    AsyncCP disconnect\n";
    #endif
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

private:
  const size_t bulkSize;
  const char bulkOpenDelimiter;
  const char bulkCloseDelimiter;
  std::ostream& outputStream;
  std::ostream& errorStream;
  std::ostream& metricsStream;

  std::shared_ptr<CommandProcessorInstance<loggingThreadsCount>> processor;

  std::shared_ptr<InputReader::InputBufferType> entryPoint{nullptr};
  std::shared_ptr<InputProcessor::InputBufferType> commandBuffer;
  std::shared_ptr<InputProcessor::OutputBufferType> bulkBuffer;

  std::mutex dataEntryLock;

  std::thread workingThread;

  SharedGlobalMetrics metrics;
};
