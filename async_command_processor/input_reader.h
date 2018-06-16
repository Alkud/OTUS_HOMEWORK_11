// input_reader.h in Otus homework#7 project

#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "broadcasters.h"
#include "smart_buffer_mt.h"
#include "async_worker.h"
#include "thread_metrics.h"

enum class InputReaderSettings
{
  MaxInputStringSize = 80
};

class InputReader : public MessageBroadcaster,
                    public MessageListener,
                    public NotificationListener,
                    public std::enable_shared_from_this<NotificationListener>,
                    public AsyncWorker<1>
{
public:

  using EntryDataType = std::list<char>;
  using InputBufferType = SmartBuffer<EntryDataType>;
  using OutputBufferType = SmartBuffer<std::string>;

  InputReader(const std::string& newWorkerName,
              const std::shared_ptr<InputBufferType>& newInputBuffer,
              const std::shared_ptr<OutputBufferType>& newOutputBuffer,
              std::ostream& newErrorOut);

  ~InputReader();

  void reactMessage(MessageBroadcaster* sender, Message message) override;

  void reactNotification(MessageListener* sender) override;

  bool threadProcess(const size_t threadIndex) override;

  void onThreadException(const std::exception& ex, const size_t threadIndex) override;

  void onTermination(const size_t threadIndex) override;

  const SharedMetrics getMetrics();

private:

  bool getNextCharacters();
  void putNextLine();

  std::shared_ptr<InputBufferType> inputBuffer;
  std::shared_ptr<OutputBufferType> outputBuffer;

  std::ostream& errorOut;

  std::stringstream tempBuffer;

  SharedMetrics threadMetrics;
};
