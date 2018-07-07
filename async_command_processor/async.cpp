// async.cpp in Otus homework#11 project

#include "async.h"
#include <iostream>
#include <mutex>
#include <memory>
#include <unordered_set>
#include <list>
#include "async_command_processor.h"

using SharedACP = std::shared_ptr<AsyncCommandProcessor<2>>;
using HandleType = SharedACP*;

//std::unordered_map<ACPPointer, std::atomic_flag> connections{};
std::unordered_set<HandleType> connections{};

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


  auto newHandle { new SharedACP(newCommandProcessor)};

  if (newCommandProcessor->connect() == true)
  {
//    connections.emplace(std::make_pair(ACPPointer{newCommandProcessor},
//                        std::atomic_flag{ATOMIC_FLAG_INIT}));

    connections.insert(newHandle);
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

//  if(connections.find(testHandle) == connections.end())
//  {
//    return;
//  }

  auto commandProcessor{*testHandle};

  try
  {
//    if (connections[commandProcessor].test_and_set(std::memory_order_acquire) == false)
//    {
//      connections[commandProcessor].clear(std::memory_order_release);
//      return;
//    }
    if (commandProcessor == nullptr
        || commandProcessor->isDisconnected() == true)
    {
      //rstd::cout << "\n------Wrong receive!-------\n";
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

  auto testHandle {reinterpret_cast<HandleType>(handle)};

//  if(connections.find(testHandle) == connections.end())
//  {
//    return;
//  }

  auto commandProcessor{*testHandle};

  try
  {

    //connections[commandProcessor].clear(std::memory_order_release);
    auto tmp = std::atomic_exchange(&commandProcessor, SharedACP{nullptr});

    tmp->disconnect();

    tmp.reset();

    delete testHandle;
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
