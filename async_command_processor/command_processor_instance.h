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
class CommandProcessorInstance : public MessageListener
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
    dataPublished{false}, dataLogged{false}, shouldExit{false},
    errorOut{errorStream}, metricsOut{metricsStream}, globalMetrics{}
  {
    /* connect broadcasters and listeners */
    externalBuffer->addNotificationListener(inputReader);
    externalBuffer->addMessageListener(inputReader);

    inputReader->addMessageListener(inputBuffer);

    inputBuffer->addMessageListener(inputProcessor);
    inputBuffer->addNotificationListener(inputProcessor);

    inputProcessor->addMessageListener(outputBuffer);

    outputBuffer->addNotificationListener(publisher);
    outputBuffer->addMessageListener(publisher);
    outputBuffer->addNotificationListener(logger);
    outputBuffer->addMessageListener(logger);

    publisher->addMessageListener(inputReader);
    logger->addMessageListener(inputReader);

    /* creating metrics*/
    globalMetrics["input reader"] = inputReader->
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

  void reactMessage();

  void run()
  {
    externalBuffer->start();
    inputBuffer->start();
    outputBuffer->start();

    publisher->start();
    logger->start();

    inputProcessor->start();

    inputReader->startAndWait();
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

  bool dataPublished;
  bool dataLogged;
  bool shouldExit;

  std::condition_variable terminationNotifier{};
  std::mutex notifierLock;

  std::ostream& errorOut;
  std::ostream& metricsOut;
  SharedGlobalMetrics globalMetrics;
};

