// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>
#include <mutex>
#include <memory>
#include "async_command_processor.h"

static std::mutex contextLock{};


async::handle_t async::connect(std::size_t bulk)
{
  if (0 == bulk)
  {
    return nullptr;
  }

  auto newCommandProcessor {new AsyncCommandProcessor<2>(
      bulk, '{', '}', std::cout, std::cerr, std::cout
    )
  };

  if (newCommandProcessor->connect() == true)
  {
    return reinterpret_cast<void*>(newCommandProcessor);
  }
  else
  {
    return nullptr;
  }
}

void async::receive(async::handle_t handle, const char* data, std::size_t size)
{
  if (nullptr == handle
      || nullptr == data
      || 0 == size)
  {
    return;
  }

  auto commandProcessor {reinterpret_cast<AsyncCommandProcessor<2>*>(handle)};

  try
  {
    std::lock_guard<std::mutex> lockContext{contextLock};
    if (commandProcessor->isDisconnected())
    {
      return;
    }

    commandProcessor->receiveData(data, size);
  }
  catch(...)
  {
    std::cout << "\n------Wrong receive!-------\n";
    return;
  }
}

void async::disconnect(async::handle_t handle)
{
  if (nullptr == handle)
  {
    return;
  }

  #ifdef NDEBUG
  #else
    //std::cout << "\n                    async::disconnect\n";
  #endif

  auto commandProcessor {reinterpret_cast<AsyncCommandProcessor<2>*>(handle)};

  try
  {
    std::lock_guard<std::mutex> lockContext{contextLock};
    commandProcessor->disconnect();
    delete commandProcessor;
  }
  catch(...)
  {
    std::cout << "\n------Wrong disconnect!-------\n";
    return;
  }
}
