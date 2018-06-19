// input_reader.cpp in Otus homework#7 project

#include "input_reader.h"
#include <string>
#include <stdexcept>
#include <mutex>

InputReader::InputReader(const std::string& newWorkerName,
    const std::shared_ptr<InputBufferType>& newInputBuffer,
    const std::shared_ptr<OutputBufferType>& newOutputBuffer,
    std::ostream& newErrorOut
  ) :
  AsyncWorker<1>{newWorkerName},
  inputBuffer{newInputBuffer},
  outputBuffer{newOutputBuffer},
  errorOut{newErrorOut},
  threadMetrics{std::make_shared<ThreadMetrics>("input reader")}
{
  if (nullptr == inputBuffer)
  {
    throw(std::invalid_argument{"Input reader source buffer not defined!"});
  }

  if (nullptr == outputBuffer)
  {
    throw(std::invalid_argument{"Input reader destination buffer not defined!"});
  }
}

InputReader::~InputReader()
{
  stop();
}

void InputReader::reactMessage(MessageBroadcaster* sender, Message message)
{
  if (messageCode(message) < 1000) // non error message
  {
    switch(message)
    {
    case Message::NoMoreData :
      if (noMoreData != true && inputBuffer.get() == sender)
      {
        #ifdef NDEBUG
        #else
          std::cout << "\n                     " << this->workerName<< " NoMoreData received\n";
        #endif

        std::lock_guard<std::mutex> lockControl{controlLock};
        noMoreData = true;
        threadNotifier.notify_all();
      }
      break;

    default:
      break;
    }
  }
  else                             // error message
  {
    if (shouldExit != true)
    {
      std::lock_guard<std::mutex> lockControl{controlLock};
      shouldExit = true;
      sendMessage(message);
    }
  }
}

void InputReader::reactNotification(NotificationBroadcaster* sender)
{
  if (inputBuffer.get() == sender)
  {
    #ifdef NDEBUG
    #else
      std::cout << this->workerName << " reactNotification\n";
    #endif

    ++notificationCount;
    threadNotifier.notify_one();
  }
}

const SharedMetrics InputReader::getMetrics()
{
  return threadMetrics;
}

bool InputReader::threadProcess(const size_t threadIndex)
{
  if (nullptr == inputBuffer)
  {
    errorMessage = Message::SourceNullptr;
    throw(std::invalid_argument{"Input reader source buffer not defined!"});
  }

  decltype(inputBuffer->getItem()) bufferReply{};
  {
    std::lock_guard<std::mutex> lockBuffer{inputBuffer->dataLock};
    bufferReply = inputBuffer->getItem(shared_from_this());
  }

  if (false == bufferReply.first)
  {
    return false;
  }

  /* Refresh metrics */
  ++threadMetrics->totalReceptionCount;

  for (const auto& element : bufferReply.second)
  {
    /* Refresh metrics */
    ++threadMetrics->totalCharacterCount;

    tempBuffer << element;
    if ('\n' == element)
    {
      putNextLine();
    }
  }
}

void InputReader::onThreadException(const std::exception& ex, const size_t threadIndex)
{
  errorOut << this->workerName << " thread #" << threadIndex << " stopped. Reason: " << ex.what() << std::endl;

  if (ex.what() == "Buffer is empty!")
  {
    errorMessage = Message::BufferEmpty;
  }

  threadFinished[threadIndex] = true;
  shouldExit = true;
  threadNotifier.notify_all();

  sendMessage(errorMessage);
}

void InputReader::onTermination(const size_t threadIndex)
{
  #ifdef NDEBUG
  #else
    std::cout << "\n                     " << this->workerName<< " all characters received\n";
  #endif

  if (true == noMoreData && notificationCount.load() == 0)
  {
    sendMessage(Message::NoMoreData);
    sendMessage(Message::AllDataReceived);
  }
}

void InputReader::putNextLine()
{
  if (nullptr == outputBuffer)
  {
    errorMessage = Message::DestinationNullptr;
    throw(std::invalid_argument{"Input reader destination buffer not defined!"});
  }

  std::string nextString{};

  std::getline(tempBuffer, nextString);

//  tempBuffer.seekg(0);

//  if (tempBuffer.fail() == true)
//  {
//    errorMessage = Message::CharacterReadingError;
//    throw(std::ios_base::failure{"Character extraction error!"});
//  }

  /* Refresh metrics */
  ++threadMetrics->totalStringCount;

  std::lock_guard<std::mutex> lockBuffer{outputBuffer->dataLock};
  outputBuffer->putItem(std::move(nextString));
}

WorkerState InputReader::getWorkerState()
{
  return state;
}
