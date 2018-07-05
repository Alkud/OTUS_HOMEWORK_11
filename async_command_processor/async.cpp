// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>
#include <mutex>
#include <memory>
#include <list>
#include "async_command_processor.h"

//static std::list<std::unique_ptr<AsyncCommandProcessor<2>>> connections{};

async::handle_t async::connect(std::size_t bulk)
{
  if (0 == bulk)
  {
    return nullptr;
  }

  auto newCommandProcessor {std::make_shared<AsyncCommandProcessor<2>>(
      bulk, '{', '}', std::cout, std::cerr, std::cout
    )
  };

  if (newCommandProcessor->connect() == true)
  {    
    return reinterpret_cast<void*>(newCommandProcessor.get());
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
    if (commandProcessor->isDisconnected())
    {
      return;
    }

    commandProcessor->receiveData(data, size);
  }
  catch(...)
  {
    #ifdef NDEBUG
    #else
      //std::cout << "\n------Wrong receive!-------\n";
    #endif

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
    commandProcessor->disconnect();
  }
  catch(...)
  {
    #ifdef NDEBUG
    #else
      //std::cout << "\n------Wrong disconnect!-------\n";
    #endif

    return;
  }
}
