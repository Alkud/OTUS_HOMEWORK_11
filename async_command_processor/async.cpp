// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>
#include <mutex>

std::mutex outputLock{};

async::handle_t async::connect(std::size_t bulk)
{
  if (0 == bulk)
  {
    return nullptr;
  }

  auto newCommandProcessor {new AsyncCommandProcessor<2>(
      outputLock, bulk, '{', '}', std::cout, std::cerr, std::cout
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
  if (nullptr == handle)
  {
    return;
  }

  auto commandProcessor {reinterpret_cast<AsyncCommandProcessor<2>*>(handle)};
  commandProcessor->receiveData(data, size);
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
  commandProcessor->disconnect();

  delete commandProcessor;
}
