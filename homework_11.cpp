// homework_11.cpp in Otus homework#11 project

#include "homework_11.h"
#include "./async_command_processor/async.h"

int homework(int argc, char* argv[], std::istream& inputStream, std::ostream& outputStream,
              std::ostream& errorStream, std::ostream& metricsStream)
{
  const size_t bulk = 10;
  auto h = async::connect(bulk);
  auto h2 = async::connect(bulk);
  async::receive(h, "1", 1);
  async::receive(h2, "1\n", 2);
  async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
  async::receive(h, "b\nc\nd\n}\n89\n", 11);
//  for (size_t i{0}; i < 1000; ++i)
//  {
//    async::receive(h, "a\n", 2);
//  }
  async::disconnect(h);
  async::disconnect(h2);

  return 0;
}
