// input_reader.h in Otus homework#7 project

#pragma once

#include <iostream>
#include <memory>
#include "broadcasters.h"
#include "smart_buffer_mt.h"
#include "async_worker.h"

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

  using InputBufferType = SmartBuffer<char>

  InputReader(const std::string& newWorkerName,
              std::istream& newInput, std::mutex& newInputLock,
              const std::shared_ptr<SmartBuffer<std::string>>& newBuffer);

  ~InputReader();

  /// Read from input stream until eof
  void read();

  void reactMessage(class MessageBroadcaster* sender, Message message) override;

  WorkerState getWorkerState();

private:

  std::istream& input;
  std::mutex& inputLock;
  std::shared_ptr<SmartBuffer<std::string>> buffer;

  bool shouldExit;

  WorkerState state;
};
