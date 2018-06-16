// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>

async::handle_t async::connect(std::size_t bulk)
{
  auto newCommandProcessor {new AsyncCommandProcessor<2>(
      bulk, '{', '}', std::cout, std::cerr, std::cout
    )
  };
  newCommandProcessor->connect();
  return reinterpret_cast<void*>(newCommandProcessor);
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

  auto commandProcessor {reinterpret_cast<AsyncCommandProcessor<2>*>(handle)};
  commandProcessor->disconnect();
  delete commandProcessor;
}
