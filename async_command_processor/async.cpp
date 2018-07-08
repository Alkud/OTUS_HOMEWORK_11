// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>
#include <mutex>
#include <memory>
#include <unordered_set>
#include <list>
#include "async_command_processor.h"

using SharedACP = std::shared_ptr<AsyncCommandProcessor<2>>;
//using HandleType = std::shared_ptr<SharedACP>;
using HandleType = SharedACP*;

std::list<HandleType> connections{};

async::handle_t async::connect(std::size_t bulk)
{
  if (0 == bulk)
  {
    return nullptr;
  }

  auto newCommandProcessor { std::make_shared<AsyncCommandProcessor<2>>(
      bulk, '{', '}', std::cout, std::cerr, std::cout
    )
  };


//  auto newHandle { std::make_shared<SharedACP>(newCommandProcessor)};
  auto newHandle { new SharedACP (newCommandProcessor)};

  if (newCommandProcessor->connect() == true)
  {
    //connections.push_back(newHandle);
    return reinterpret_cast<void*>(newHandle);
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

  #ifdef NDEBUG
  #else
    //std::cout << "\n                    async::receive\n";
  #endif

  auto testHandle {reinterpret_cast<HandleType>(handle)};

  auto commandProcessor{*testHandle};

  try
  {
    if (commandProcessor == nullptr)
    {
      return;
    }

    if (commandProcessor->isDisconnected() != true)
    {
      commandProcessor->receiveData(data, size);
    }

    return;
  }
  catch(...)
  {
    #ifdef NDEBUG
    #else
      std::cout << "\n------Wrong receive!-------\n";
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

  auto testHandle {reinterpret_cast<HandleType>(handle)};

  //auto commandProcessor{*testHandle};

  try
  {    
    auto tmp = std::atomic_exchange(testHandle, SharedACP{nullptr});

    tmp->disconnect();

    //std::this_thread::sleep_for(150ms);

    #ifdef NDEBUG
    #else
      std::cout << "\n------destroy ACP-------\n";
    #endif

    tmp.reset();



    #ifdef NDEBUG
    #else
      std::cout << "\n------delete handle-------\n";
    #endif

    delete testHandle;

  }
  catch(...)
  {
    #ifdef NDEBUG
    #else
      std::cout << "\n------Wrong disconnect!-------\n";
    #endif

    return;
  }
}
