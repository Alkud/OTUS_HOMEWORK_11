// input_reader.cpp in Otus homework#7 project

#include "input_reader.h"
#include <string>
#include <stdexcept>
#include <mutex>

InputReader::InputReader(const std::string& newWorkerName,
                         const std::shared_ptr<InputBufferType>& newInputBuffer,
                         const std::shared_ptr<OutputBufferType>& newOutputBuffer,
                         std::ostream& newErrorOut) :
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



void InputReader::read()
{
  std::string nextString{};
  state = WorkerState::Started;
  try
  {
    std::lock_guard<std::mutex> lockInput{inputLock};
    while(shouldExit!= true
          && std::getline(input, nextString))
    {
      if (nextString.size() > (size_t)InputReaderSettings::MaxInputStringSize)
      {
        std::cerr << "Maximum command length exceeded! String truncated";
        nextString = nextString.substr((size_t)InputReaderSettings::MaxInputStringSize);
      }
      std::unique_lock<std::mutex> lockBuffer{buffer->dataLock};
      buffer->putItem(nextString);
      lockBuffer.unlock();
    }
    sendMessage(Message::NoMoreData);
    state = WorkerState::Finished;
  }
  catch(std::exception& ex)
  {
    #ifdef _DEBUG
      std::cout << "\n                     reader ABORT\n";
    #endif

    sendMessage(Message::Abort);
    std::cerr << ex.what();
    state = WorkerState::Finished;
  }

}

void InputReader::reactMessage(MessageBroadcaster* sender, Message message)
{
  switch(message)
  {
  case Message::NoMoreData :
    if (noMoreData != true && inputBuffer.get() == sender)
    {
      #ifdef _DEBUG
        std::cout << "\n                     " << this->workerName<< " NoMoreData received\n";
      #endif

      std::lock_guard<std::mutex> lockControl{controlLock};
      noMoreData = true;
      threadNotifier.notify_all();
    }
    break;

  case Message::Abort :
    if (shouldExit != true)
    {
      shouldExit = true;
      sendMessage(Message::Abort);
    }
    break;
  }
}

void InputReader::reactNotification(MessageListener* sender)
{
  if (inputBuffer.get() == sender)
  {
    #ifdef _DEBUG
      std::cout << this->workerName << " reactNotification\n";
    #endif

    ++notificationCount;
    threadNotifier.notify_one();
  }
}

bool InputReader::threadProcess(const size_t threadIndex)
{
  getNextCharacters();
}

void InputReader::onThreadException(const std::exception& ex, const size_t threadIndex)
{
  errorOut << this->workerName << " thread #" << threadIndex << " stopped. Reason: " << ex.what() << std::endl;

  threadFinished[threadIndex] = true;
  shouldExit = true;
  threadNotifier.notify_all();

  sendMessage(Message::Abort);
}

void InputReader::onTermination(const size_t threadIndex)
{

}

bool InputReader::getNextCharacters()
{
  if (nullptr == inputBuffer)
  {
    throw(std::invalid_argument{"Input reader source buffer not defined!"});
  }

  decltype(inputBuffer->getItem()) bufferReply{};
  {
    std::lock_guard<std::mutex> lockBuffer{inputBuffer->dataLock};
    bufferReply = inputBuffer->getItem(shared_from_this());
  }

  if (false = bufferReply.first)
  {
    return false;
  }

  for (const auto& element : bufferReply.second)
  {
    if ('\n' == element)
    {
      putNextLine();
    }
    tempBuffer << element;
  }
}

void InputReader::putNextLine()
{
  if (nullptr == inputBuffer)
  {
    throw(std::invalid_argument{"Input reader destination buffer not defined!"});
  }

  std::string nextString{};

  std::getline(tempBuffer, nextString);

  if (tempBuffer.fail())
  {
    errorOut << "Cannot extract characters" << std::endl;
    throw(std::ios_base::failure{"Character extraction error!"});
  }

  std::lock_guard<std::mutex> lockBuffer{outputBuffer->dataLock};
  outputBuffer->putItem(std::move(nextString));
}

WorkerState InputReader::getWorkerState()
{
  return state;
}
