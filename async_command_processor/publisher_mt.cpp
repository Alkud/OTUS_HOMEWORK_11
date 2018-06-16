// publisher.cpp in Otus homework#11 project

#include "publisher_mt.h"


Publisher::Publisher(const std::string& newWorkerName,
                     const std::shared_ptr<SmartBuffer<std::pair<size_t, std::string> > >& newBuffer,
                     std::ostream& newOutput, std::mutex& newOutpuLock,
                     std::ostream& newErrorOut) :
  AsyncWorker<1>{newWorkerName},
  buffer{newBuffer}, output{newOutput}, outputLock{newOutpuLock},
  threadMetrics{std::make_shared<ThreadMetrics>("publisher")},
  errorOut{newErrorOut}
{
  if (nullptr == buffer)
  {
    throw(std::invalid_argument{"Publisher source buffer not defined!"});
  }
}

Publisher::~Publisher()
{
  stop();
}

void Publisher::reactNotification(NotificationBroadcaster* sender)
{
  if (buffer.get() == sender)
  {
    #ifdef _DEBUG
      std::cout << this->workerName << " reactNotification\n";
    #endif

    ++notificationCount;    
    threadNotifier.notify_one();
  }
}

void Publisher::reactMessage(MessageBroadcaster* sender, Message message)
{
  if (messageCode(message) < 1000) // non error message
  {
    switch(message)
    {
    case Message::NoMoreData :
      if (noMoreData != true && buffer.get() == sender)
      {
        #ifdef _DEBUG
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

const SharedMetrics Publisher::getMetrics()
{
  return threadMetrics;
}

bool Publisher::threadProcess(const size_t threadIndex)
{
  if (nullptr == buffer)
  {
    errorMessage = Message::SourceNullptr;
    throw(std::invalid_argument{"Logger source buffer not defined!"});
  }

  decltype(buffer->getItem()) bufferReply{};
  {
    std::lock_guard<std::mutex> lockBuffer{buffer->dataLock};
    bufferReply = buffer->getItem(shared_from_this());
  }

  if (false == bufferReply.first)
  {
    return false;
  }

  auto nextBulkInfo{bufferReply.second};

  std::lock_guard<std::mutex> lockOutput{outputLock};
  output << nextBulkInfo.second << '\n';

  /* Refresh metrics */
  ++threadMetrics->totalBulkCount;
    threadMetrics->totalCommandCount
      += std::count(nextBulkInfo.second.begin(),
                    nextBulkInfo.second.end(), ',') + 1;

  return true;
}

void Publisher::onThreadException(const std::exception& ex, const size_t threadIndex)
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

void Publisher::onTermination(const size_t threadIndex)
{
  #ifdef _DEBUG
    std::cout << "\n                     " << this->workerName<< " AllDataLogged\n";
  #endif

  if (true == noMoreData && notificationCount.load() == 0)
  {
    sendMessage(Message::AllDataPublsihed);
  }
}
