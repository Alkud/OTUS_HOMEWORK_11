// command_processor.h in Otus homework#11 project

#pragma once

#include <memory>
#include <mutex>
#include <list>
#include <thread>
#include <functional>
#include <condition_variable>
#include "input_reader.h"
#include "input_processor.h"
#include "smart_buffer_mt.h"
#include "publisher_mt.h"
#include "logger_mt.h"

template<size_t loggingThreadsCount = 2u>
class CommandProcessorInstance :  public MessageBroadcaster,
                                  public MessageListener,
                                  public std::enable_shared_from_this<MessageListener>
{
public:

  CommandProcessorInstance
  (
    const size_t bulkSize = 3,
    const char bulkOpenDelimiter = '{',
    const char bulkCloseDelimiter = '}',
    std::ostream& outputStream = std::cout,
    std::ostream& errorStream = std::cerr,
    std::ostream& metricsStream = std::cout
  ) :
    /* creating buffers */
    externalBuffer{std::make_shared<InputReader::InputBufferType>("character buffer", errorStream)},
    inputBuffer{std::make_shared<InputProcessor::InputBufferType>("command buffer", errorStream)},
    outputBuffer{std::make_shared<InputProcessor::OutputBufferType>("bulk buffer", errorStream)},

    /* creating logger */
    logger{
      std::make_shared<Logger<loggingThreadsCount>>(
      "logger", outputBuffer, "", errorStream

    )},

    /* creating publisher */
    publisher{
      std::make_shared<Publisher>(
      "publisher", outputBuffer, outputStream, outputStreamLock,
      errorStream
    )},

    /* creating command processor */
    inputProcessor{
      std::make_shared<InputProcessor>(
      "input processor ", bulkSize,
      bulkOpenDelimiter, bulkCloseDelimiter,
      inputBuffer, outputBuffer,
      errorStream
    )},

    /* creating command reader */
    inputReader{
      std::make_shared<InputReader>(
      "input reader",
      externalBuffer, inputBuffer,
      errorStream
    )},

    dataReceived{false}, dataPublished{false},
    dataLogged{false}, shouldExit{false},
    errorOut{errorStream}, metricsOut{metricsStream}, globalMetrics{}
  {
    /* connect broadcasters and listeners */
    this->addMessageListener(externalBuffer);

    externalBuffer->addNotificationListener(inputReader);
    externalBuffer->addMessageListener(inputReader);

    inputReader->addMessageListener(inputBuffer);
//    inputReader->addMessageListener(shared_from_this());

    inputBuffer->addMessageListener(inputProcessor);
    inputBuffer->addNotificationListener(inputProcessor);

    inputProcessor->addMessageListener(outputBuffer);

    outputBuffer->addNotificationListener(publisher);
    outputBuffer->addMessageListener(publisher);
    outputBuffer->addNotificationListener(logger);
    outputBuffer->addMessageListener(logger);

//    publisher->addMessageListener(shared_from_this());
//    logger->addMessageListener(shared_from_this());

    /* creating metrics*/
    globalMetrics["input reader"] = inputReader->getMetrics();
    globalMetrics["input processor"] = inputProcessor->getMetrics();
    globalMetrics["publisher"] = publisher->getMetrics();

    SharedMultyMetrics loggerMetrics{logger->getMetrics()};
    for (size_t idx{0}; idx < loggingThreadsCount; ++idx)
    {
      auto threadName = std::string{"logger thread#"} + std::to_string(idx);
      globalMetrics[threadName] = loggerMetrics[idx];
    }
  }

  ~CommandProcessorInstance()
  {

  }

  void reactMessage(MessageBroadcaster* sender, Message message)
  {
    if (messageCode(message) < 1000) // non error message
    {
      switch(message)
      {
      case Message::AllDataReceived :
        {
          #ifdef _DEBUG
            std::cout << "\n                     AllDataReceived received\n";
          #endif

          std::lock_guard<std::mutex> lockControl{controlLock};
          dataReceived = true;
        }
        controlNotifier.notify_all();
        break;

      case Message::AllDataLogged :
        {
          #ifdef _DEBUG
            std::cout << "\n                     AllDataLogged received\n";
          #endif

          std::lock_guard<std::mutex> lockControl{controlLock};
          dataLogged = true;
        }
        controlNotifier.notify_all();
        break;

      case Message::AllDataPublsihed :
        {
          #ifdef _DEBUG
            std::cout << "\n                     AllDataReceived received\n";
          #endif

          std::lock_guard<std::mutex> lockControl{controlLock};
          dataPublished = true;
        }
        controlNotifier.notify_all();
        break;

      default:
        break;
      }
    }
    else                             // error message
    {
      if (shouldExit != true)
      {
        {
          std::lock_guard<std::mutex> lockControl{controlLock};
          shouldExit = true;
          errorMessage = message;
        }
        controlNotifier.notify_all();
      }
    }
  }

  SharedGlobalMetrics run()
  {
    try
    {
      inputReader->addMessageListener(shared_from_this());
      publisher->addMessageListener(shared_from_this());
      logger->addMessageListener(shared_from_this());


      externalBuffer->start();
      inputBuffer->start();
      outputBuffer->start();

      publisher->start();
      logger->start();

      inputProcessor->start();

      inputReader->startAndWait();

      /* wait for data processing termination */
      while (shouldExit != true
             && ((dataReceived && dataLogged && dataPublished) != true))
      {
        #ifdef _DEBUG
          std::cout << "\n                     CPInstance waiting\n";
        #endif

        std::unique_lock<std::mutex> lockControl{controlLock};
        controlNotifier.wait_for(lockControl, std::chrono::seconds{1}, [this]()
        {
          return (shouldExit) || (dataReceived && dataLogged && dataPublished);
        });
        lockControl.unlock();
      }

      #ifdef _DEBUG
        std::cout << "\n                     CPInsatnce waiting ended\n";
      #endif

      if (shouldExit == true)
      {
        sendMessage(errorMessage);
      }

      /* waiting for all workers to finish */
      while(inputReader->getWorkerState() != WorkerState::Finished
            && inputProcessor->getWorkerState() != WorkerState::Finished
            && inputBuffer->getWorkerState() != WorkerState::Finished
            && outputBuffer->getWorkerState() != WorkerState::Finished
            && logger->getWorkerState() != WorkerState::Finished
            && publisher->getWorkerState() != WorkerState::Finished)
      {}

      if (shouldExit == true)
      {
        errorOut << "Abnormal termination\n";
        errorOut << "Error code: " << messageCode(errorMessage);
      }

      #ifdef _DEBUG
        std::cout << "\n                     CP metrics output\n";
      #endif

      return globalMetrics;
    }
    catch(const std::exception& ex)
    {
      errorOut << ex.what();
      return globalMetrics;
    }
  }

  const std::shared_ptr<InputReader::InputBufferType>&
  getEntryPoint() const
  { return externalBuffer; }


  const std::shared_ptr<InputProcessor::InputBufferType>&
  getInputBuffer() const
  { return inputBuffer; }


  const std::shared_ptr<InputProcessor::OutputBufferType>&
  getOutputBuffer() const
  { return outputBuffer; }


private:
  std::shared_ptr<InputReader::InputBufferType> externalBuffer;
  std::shared_ptr<SmartBuffer<std::string>> inputBuffer;
  std::shared_ptr<SmartBuffer<std::pair<size_t, std::string>>> outputBuffer;
  std::shared_ptr<InputReader> inputReader;
  std::shared_ptr<Logger<loggingThreadsCount>> logger;
  std::shared_ptr<Publisher> publisher;
  std::shared_ptr<InputProcessor> inputProcessor;

  std::mutex inputStreamLock{};
  std::mutex outputStreamLock{};

  bool dataReceived;
  bool dataPublished;
  bool dataLogged;
  bool shouldExit;
  std::condition_variable controlNotifier{};
  std::mutex controlLock;

  std::ostream& errorOut;
  std::ostream& metricsOut;
  SharedGlobalMetrics globalMetrics;

  Message errorMessage{Message::SystemError};
};

