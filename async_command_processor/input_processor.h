// input_processor.h in Otus homework#7 project

#pragma once

#include <memory>
#include <chrono>
#include <ctime>
#include "smart_buffer_mt.h"
#include "thread_metrics.h"


class InputProcessor : public NotificationListener,
                       public MessageBroadcaster,
                       public MessageListener,
                       public std::enable_shared_from_this<InputProcessor>,
                       public AsyncWorker<1>
{
public:

  using InputBufferType = SmartBuffer<std::string>;
  using OutputBufferType = SmartBuffer<std::pair<size_t, std::string>>;

  InputProcessor(const std::string& newWorkerName,
                 const size_t newBulkSize,
                 const char newBulkOpenDelimiter,
                 const char newBulkCloseDelimiter,
                 const std::shared_ptr<SmartBuffer<std::string>>& newInputBuffer,
                 const std::shared_ptr<SmartBuffer<std::pair<size_t, std::string>>>& newOutputBuffer,
                 std::ostream& newErrorOut);

  ~InputProcessor();

  void reactNotification(NotificationBroadcaster* sender) override;

  void reactMessage(MessageBroadcaster* sender, Message message) override;

  const SharedMetrics getMetrics();

  WorkerState getWorkerState();

private:

  bool threadProcess(const size_t threadIndex) override;
  void onThreadException(const std::exception& ex, const size_t threadIndex) override;
  void onTermination(const size_t threadIndex) override;

  void sendCurrentBulk();
  void startNewBulk();
  void closeCurrentBulk();
  void addCommandToBulk(std::string&& newCommand);

  const size_t bulkSize;
  const std::string bulkOpenDelimiter;
  const std::string bulkCloseDelimiter;

  std::shared_ptr<InputBufferType> inputBuffer;
  std::shared_ptr<OutputBufferType> outputBuffer;

  std::deque<std::string> tempBuffer;
  bool customBulkStarted;
  size_t nestingDepth;
  std::chrono::time_point<std::chrono::system_clock> bulkStartTime;

  std::ostream& errorOut;

  SharedMetrics threadMetrics;

  Message errorMessage{Message::SystemError};
};
