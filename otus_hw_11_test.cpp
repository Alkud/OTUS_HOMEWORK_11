// otus_hw_11_test.cpp in Otus homework#11 project

#define BOOST_TEST_MODULE OTUS_HW_11_TEST

#include <boost/test/unit_test.hpp>
#include "homework_11.h"
#include "./async_command_processor/async.h"
#include "./async_command_processor/async_command_processor.h"
//#include "new_delete.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <unordered_set>

enum class DebugOutput
{
  debug_on,
  debug_off
};


/* Helper functions */
std::array<std::vector<std::string>, 3>
getProcessorOutput
(
  const std::string& inputString,
  char openDelimiter,
  char closeDelimiter,
  size_t bulkSize,
  DebugOutput debugOutput,
  SharedGlobalMetrics metrics
)
{
  std::stringstream inputStream{inputString};  
  std::stringstream outputStream{};
  std::stringstream errorStream{};
  std::stringstream metricsStream{};  

  {
    AsyncCommandProcessor<2> testProcessor {
      bulkSize, openDelimiter, closeDelimiter,
      outputStream, errorStream, metricsStream
    };

    testProcessor.run(true);

    metrics = testProcessor.getMetrics();
  }

  std::array<std::vector<std::string>, 3> result {};

  std::string tmpString{};
  while(std::getline(outputStream, tmpString))
  {
    if (DebugOutput::debug_on == debugOutput)
    {
      std::cout << tmpString << '\n';
    }
    result[0].push_back(tmpString);
  }

  while(std::getline(errorStream, tmpString))
  {
    result[1].push_back(tmpString);
  }

  while(std::getline(metricsStream, tmpString))
  {
    result[2].push_back(tmpString);
  }

  return result;
}


using SharedACP = std::shared_ptr<AsyncCommandProcessor<2>>;
using HandleType = std::shared_ptr<SharedACP>;

std::mutex mockConnectionLock{};
std::list<HandleType> mockConnections{};

void*
mockConnect(
    size_t bulkSize,
    std::stringstream& outputStream,
    std::stringstream& errorStream
)
{
  if (0 == bulkSize)
  {
    return nullptr;
  }

  auto newCommandProcessor { std::make_shared<AsyncCommandProcessor<2>>(
      bulkSize, '{', '}', outputStream, errorStream, outputStream
    )
  };


  auto newHandle { std::make_shared<SharedACP>(newCommandProcessor)};

  if (newCommandProcessor->connect() == true)
  {
    std::lock_guard<std::mutex> lockMockConnection{mockConnectionLock};
    mockConnections.push_back(newHandle);
    return reinterpret_cast<void*>(newHandle.get());
  }
  else
  {
    return nullptr;
  }
}

void checkMetrics(const SharedGlobalMetrics& metrics,
  const size_t receptionCountExpected,
  const size_t characterCountExpected,
  const size_t stringCountExpected,
  const size_t commandCountExpected,
  const size_t bulkCountExpected,
  const size_t loggingThreadCount
  )
{
  BOOST_CHECK(metrics.size() == 3 + loggingThreadCount);

  BOOST_CHECK(metrics.at("input reader")->totalReceptionCount == receptionCountExpected);
  BOOST_CHECK(metrics.at("input reader")->totalCharacterCount == characterCountExpected);
  BOOST_CHECK(metrics.at("input reader")->totalStringCount == stringCountExpected);

  BOOST_CHECK(metrics.at("input processor")->totalStringCount == stringCountExpected);
  BOOST_CHECK(metrics.at("input processor")->totalCommandCount == commandCountExpected);
  BOOST_CHECK(metrics.at("input processor")->totalBulkCount == bulkCountExpected);

  BOOST_CHECK(metrics.at("publisher")->totalCommandCount == commandCountExpected);
  BOOST_CHECK(metrics.at("publisher")->totalBulkCount == bulkCountExpected);

  ThreadMetrics loggingMetrics{"loggers all threads"};

  for (size_t idx{0}; idx < loggingThreadCount; ++idx)
  {
    auto threadName = std::string{"logger thread#"} + std::to_string(idx);
    loggingMetrics += *metrics.at(threadName);
  }

  BOOST_CHECK (loggingMetrics == *metrics.at("publisher"));
}

BOOST_AUTO_TEST_SUITE(homework_11_test)

BOOST_AUTO_TEST_CASE(homework_11_test)
{
  try
  {
    std::stringstream outputStream{};
    std::stringstream errorStream{};
    std::stringstream metricsStream{};
    SharedGlobalMetrics metrics1{};
    SharedGlobalMetrics metrics2{};

    const size_t bulk = 10;

    auto h = mockConnect(bulk, outputStream, errorStream);
    auto h2 = mockConnect(bulk, outputStream, errorStream);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);

    metrics1 = (*reinterpret_cast<HandleType::element_type*>(h))->getMetrics();
    metrics2 = (*reinterpret_cast<HandleType::element_type*>(h2))->getMetrics();

    async::disconnect(h);
    async::disconnect(h2);

    BOOST_CHECK(outputStream.str() ==
                "bulk: 1, 2, 3, 4, 5, 6\n"
                "bulk: a, b, c, d\n"
                "bulk: 89\n"
                "bulk: 1\n");

    BOOST_CHECK(errorStream.str().empty() == true);

    checkMetrics(metrics1, 3, 27, 13, 11, 3, 2);

    checkMetrics(metrics2, 1, 2, 1, 1, 1, 2);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "homework_test failed: " << ex.what() << std::endl;
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(multithread_connect_disconnect)
{
  try
  {
    std::vector<std::future<bool>> futureResults{};

    for (size_t idx{0}; idx < 10; ++idx)
    {
      futureResults.push_back(
        std::async(
          std::launch::async, []()
          {
            try
            {
              auto handle {async::connect(5)};
              async::disconnect(handle);
              return true;
            }
            catch(const std::exception& ex)
            {
              std::cerr << ex.what() << std::endl;
              return false;
            }
          }
        )
      );
    }

    for (auto& result : futureResults)
    {
      if (result.valid())
      {
        BOOST_CHECK(result.get() == true);
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << "multithread_connect_disconnect failed: " << ex.what() << std::endl;
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(multithread_receive_test)
{
  try
  {
    std::stringstream outputStream{};
    std::stringstream errorStream{};
    std::stringstream metricsStream{};
    SharedGlobalMetrics metrics1{};
    SharedGlobalMetrics metrics2{};

    const size_t bulk = 5;

    auto handle = mockConnect(bulk, outputStream, errorStream);

    std::vector<std::future<bool>> futureResults{};

    /* start 10 threads putting data to the same buffer */
    for (size_t idx{0}; idx < 10; ++idx)
    {
      futureResults.push_back(
        std::async(
          std::launch::async, [](void* h, size_t startValue)
          {
            try
            {
              std::stringstream sendBuffer{};
              sendBuffer << std::fixed << std::setw(3) << std::setfill('0');
              sendBuffer << 10 * startValue << '\n';
              auto stringToReceive{sendBuffer.str()};
              async::receive(h, stringToReceive.c_str(), stringToReceive.size());
              return true;
            }
            catch(...)
            {
              return false;
            }
          },
          handle, idx
          )
        );
    }

    /* make sure all data is sent */
    for (auto& result : futureResults)
    {
      if (result.valid())
      {
        BOOST_CHECK(result.get() == true);
      }
    }

    auto metrics = (*reinterpret_cast<HandleType::element_type*>(handle))->getMetrics();

    async::disconnect(handle);

    /* make sure all characters and strings are received */
    /* and all commands are properly split into bulks */
    checkMetrics(metrics, 10, 40, 10, 10, 2, 2);

    auto processorOutput{outputStream.str()};

    BOOST_CHECK(processorOutput.find("000") != std::string::npos);
    BOOST_CHECK(processorOutput.find("010") != std::string::npos);
    BOOST_CHECK(processorOutput.find("020") != std::string::npos);
    BOOST_CHECK(processorOutput.find("030") != std::string::npos);
    BOOST_CHECK(processorOutput.find("040") != std::string::npos);
    BOOST_CHECK(processorOutput.find("050") != std::string::npos);
    BOOST_CHECK(processorOutput.find("060") != std::string::npos);
    BOOST_CHECK(processorOutput.find("070") != std::string::npos);
    BOOST_CHECK(processorOutput.find("080") != std::string::npos);
    BOOST_CHECK(processorOutput.find("090") != std::string::npos);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "multithread_receive_test failed: " << ex.what() << std::endl;
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(abnormal_usage_test)
{
  BOOST_CHECK(async::connect(0) == nullptr);

  BOOST_CHECK_NO_THROW(async::disconnect(nullptr));

  BOOST_CHECK_NO_THROW(async::receive(nullptr, "should not be sent", 123));

  auto handle{async::connect(2)};
  async::receive(handle, "should not be received", 0);
  auto metrics = (*reinterpret_cast<HandleType::element_type*>(handle))->getMetrics();
  async::disconnect(handle);
  checkMetrics(metrics, 0, 0, 0, 0, 0, 2);
}

BOOST_AUTO_TEST_CASE(unterminated_string_test)
{
  try
  {
    std::stringstream outputStream{};
    std::stringstream errorStream{};
    std::stringstream metricsStream{};
    SharedGlobalMetrics metrics{};

    const size_t bulk = 10;

    auto handle = mockConnect(bulk, outputStream, errorStream);
    async::receive(handle, "10", 2);
    async::receive(handle, "\n11\n12\n13\n14\n15\n{\nA\n", 22);
    async::receive(handle, "B\nC\nD\n}", 7);

    metrics = (*reinterpret_cast<HandleType::element_type*>(handle))->getMetrics();

    async::disconnect(handle);

    /* custom bulk should be ignored due to lack of new line character */
    /* after bulk closing brace */
    BOOST_CHECK(outputStream.str() ==
                "bulk: 10, 11, 12, 13, 14, 15\n");

    BOOST_CHECK(errorStream.str().empty() == true);

    checkMetrics(metrics, 3, 31, 11, 6, 1, 2);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "homework_test failed: " << ex.what() << std::endl;
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(max_string_length_test)
{
  try
  {
    std::stringstream outputStream{};
    std::stringstream errorStream{};
    std::stringstream metricsStream{};
    SharedGlobalMetrics metrics{};

    const size_t bulk = 10;

    auto handle = mockConnect(bulk, outputStream, errorStream);
    auto testString{std::string(100, 'R') + "\n"};
    async::receive(handle, testString.c_str(), 101);

    metrics = (*reinterpret_cast<HandleType::element_type*>(handle))->getMetrics();

    async::disconnect(handle);

    auto expectedString{std::string{"bulk: "} + std::string(80, 'R') + "\n"};

    BOOST_CHECK(outputStream.str() == expectedString);

    /* error message should be sent */
    BOOST_CHECK(errorStream.str().find("String truncated") != std::string::npos);

    checkMetrics(metrics, 1, 101, 1, 1, 1, 2);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "homework_test failed: " << ex.what() << std::endl;
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()

