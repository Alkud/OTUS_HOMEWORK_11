#pragma once

#include <stdint.h>
#include <cstddef>
#include <new>
#include <atomic>
#include <cstdlib>

namespace my {

  std::atomic<std::size_t> free_counter{0};

  std::atomic<std::size_t> malloc_counter{0};

  void* malloc(std::size_t size)  noexcept (false)
  {
    void* p = std::malloc(size);
     ++malloc_counter;
    return p;
  }

  void free(void* p) noexcept
  {
    ++free_counter;
    std::free(p);
    return;
  }

} 

extern "C++" {

void* operator new(std::size_t size) noexcept (false)
{
    return my::malloc(size);
}

void operator delete(void* p) noexcept
{
    my::free(p);
}

void* operator new[](std::size_t size) noexcept (false)
{
    return my::malloc(size);
}

void operator delete[](void* p) throw()
{
    my::free(p);
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return my::malloc(size);
}

void operator delete(void* p, const std::nothrow_t&) noexcept
{
    my::free(p);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return my::malloc(size);
}

void operator delete[](void* p, const std::nothrow_t&) noexcept
{
    my::free(p);
}

void operator delete(void* p, long unsigned int) noexcept
{
    my::free(p);
}

void operator delete [](void* p, long unsigned int) noexcept
{
    my::free(p);
}

}
