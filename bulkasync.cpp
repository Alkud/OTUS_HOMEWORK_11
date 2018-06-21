// bulkasync.cpp in Otus homework#11 project

#include "./homework_11.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[])
{
  try
  {
    homework();
  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what();
  }
  return 0;
}
