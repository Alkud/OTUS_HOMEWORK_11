// otus_hw_11_test.cpp in Otus homework#11 project

#define BOOST_TEST_MODULE OTUS_HW_10_TEST

#include <boost/test/unit_test.hpp>
#include "homework_11.h"
#include "./async_command_processor/async_command_processor.h"


#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <vector>

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
  DebugOutput debugOutput
)
{
  std::stringstream inputStream{inputString};  
  std::stringstream outputStream{};
  std::stringstream errorStream{};
  std::stringstream metricsStream{};

  {
  const AsyncCommandProcessor<2> testProcessor {
    bulkSize, openDelimiter, closeDelimiter,
    outputStream, errorStream, metricsStream
  };

  //testProcessor.run();

  //std::this_thread::sleep_for(std::chrono::milliseconds{200});

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


auto parseMetrics(std::stringstream& metricsStream)
{
  std::string threadMetrics{};
  size_t searchStartPosition{};
  size_t digitPosition{};

  std::vector<std::vector<int>> result;
  while (std::getline(metricsStream, threadMetrics))
  {
    result.push_back(std::vector<int>{});
    int nextNumber{};
    std::string tempString{};
    std::stringstream threadMetricsStream{threadMetrics};
    while (!threadMetricsStream.eof())
    {
      threadMetricsStream >> tempString;
      if (std::stringstream{tempString} >> nextNumber)
      {
        result.back().push_back(nextNumber);
      }
      tempString = " ";
    }
  }
  return result;
}

void checkMetrics(std::stringstream& metricsStream,
                  int stringsExpected, int commandsExpected, int bulksExpected)
{
  auto numericMetrics {parseMetrics(metricsStream)};

  BOOST_CHECK(numericMetrics.size() == 4);
  BOOST_CHECK(numericMetrics[0].size() == 3);
  BOOST_CHECK(numericMetrics[1].size() == 2);
  BOOST_CHECK(numericMetrics[2].size() == 2);
  BOOST_CHECK(numericMetrics[3].size() == 2);

  int mainStringsCount{numericMetrics[0][0]};
  int mainCommandsCount{numericMetrics[0][1]};
  int mainBulksCount{numericMetrics[0][2]};

  int logBulksCount{numericMetrics[1][0]};
  int logCommandsCount{numericMetrics[1][1]};

  int fileOneBulksCount{numericMetrics[2][0]};
  int fileOneCommandsCount{numericMetrics[2][1]};

  int fileTwoBulksCount{numericMetrics[3][0]};
  int fileTwoCommandsCount{numericMetrics[3][1]};

  BOOST_CHECK(mainStringsCount == stringsExpected);
  BOOST_CHECK(mainCommandsCount == commandsExpected);
  BOOST_CHECK(mainBulksCount == bulksExpected);

  BOOST_CHECK(logCommandsCount == commandsExpected);
  BOOST_CHECK(logBulksCount == bulksExpected);

  BOOST_CHECK(fileOneCommandsCount + fileTwoCommandsCount == commandsExpected);
  BOOST_CHECK(fileOneBulksCount + fileTwoBulksCount == bulksExpected);
}

BOOST_AUTO_TEST_SUITE(homework_10_test)

BOOST_AUTO_TEST_CASE(objects_creation_failure)
{
  std::mutex dummyMutex{};
  /* can't create input reader with null buffer pointer */
  //BOOST_CHECK_THROW((InputReader{std::cin, dummyMutex, nullptr}), std::invalid_argument);
  /* can't create publisher with null buffer pointer */
//  BOOST_CHECK_THROW((Publisher{nullptr, std::cout, dummyMutex}), std::invalid_argument);
//  /* can't create logger with null buffer pointer */
//  BOOST_CHECK_THROW((Logger<2>{nullptr, ""}), std::invalid_argument);
}

//BOOST_AUTO_TEST_CASE(log_file_creation_failure)
//{
//  const auto bulkBuffer{std::make_shared<SmartBuffer<std::pair<size_t, std::string>>>("bulk buffer")};
//  std::stringstream outputStream{};
//  std::stringstream metricsStream{};
//  std::string badDirectoryName{"/non_existing_directory/"};

//  {
//    /* use bad directory name as constructor parameter */
//    const auto badLogger{
//      std::make_shared<Logger<2>>(
//            bulkBuffer, badDirectoryName,
//            outputStream, metricsStream
//            )
//    };

//    /* create a dummy message broadcaster */
//    MessageBroadcaster dummyBroadcaster{};
//    dummyBroadcaster.addMessageListener(bulkBuffer);

//    /* connect buffer to logger */
//    bulkBuffer->addNotificationListener(badLogger);
//    bulkBuffer->addMessageListener(badLogger);

//    badLogger->start();

//    /* putting some data to the buffer results in error message */
//    bulkBuffer->putItem(std::make_pair<size_t, std::string>(1234, "bulk"));

//    dummyBroadcaster.sendMessage(Message::NoMoreData);

//    std::this_thread::sleep_for(std::chrono::milliseconds{100});
//  }

//  /* get error message string */
//  std::string errorMessage{outputStream.str()};

//  /* error message sholud contain expected file name */
//  BOOST_CHECK(errorMessage.find("1234_1.log") != std::string::npos);

//  /* get metrics string */
//  std::string metrics{metricsStream.str()};

//  /* metrics sholud contain expected text */
//  BOOST_CHECK(std::string("file thread #0 - 0 bulk(s), 0 command(s)\n"
//                          "file thread #1 - 0 bulk(s), 0 command(s)\n") == metrics);
//}

//BOOST_AUTO_TEST_CASE(trying_get_from_empty_buffer)
//{
//  const auto emptyBuffer{std::make_shared<SmartBuffer<std::pair<size_t, std::string>>>()};

//  /* create a dummy message broadcaster */
//  MessageBroadcaster dummyBroadcaster{};
//  dummyBroadcaster.addMessageListener(emptyBuffer);

//  /* emptyBuffer.getItem() should throw an exception */
//  BOOST_CHECK_THROW((emptyBuffer->getItem()), std::out_of_range);
//  dummyBroadcaster.sendMessage(Message::NoMoreData);
//}



//BOOST_AUTO_TEST_CASE(no_command_line_parameters)
//{
//  try
//  {
//    /* user input imitation: entering bulk size */
//    std::stringstream inputStream{"-1\n"
//                                  "2\n"};

//    std::stringstream outputStream{};
//    std::stringstream errorStream{};
//    std::stringstream metricsStream{};
//    /* comand line arguments */
//    char* arg[]{"/home/user/bulk"};

//    {
//      homework(1, arg, inputStream, outputStream, errorStream, metricsStream);
//    }

//    /* application outpur should contain expected text*/
//    BOOST_CHECK(outputStream.str() ==
//                "\nPlease enter bulk size (must be greater than 0): "
//                "\nPlease enter bulk size (must be greater than 0): ");

//    /* metrics sholud contain expected text */
//    BOOST_CHECK(metricsStream.str() ==
//                "main thread - 0 string(s), 0 command(s), 0 bulk(s)\n"
//                "log thread - 0 bulk(s), 0 command(s)\n"
//                "file thread #0 - 0 bulk(s), 0 command(s)\n"
//                "file thread #1 - 0 bulk(s), 0 command(s)\n");

//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(empty_input_test)
//{
//  try
//  {
//    auto processorOutput{
//      getProcessorOutput(std::string{}, '{', '}', 3, DebugOutput::debug_off)
//    };

//    /* metrics sholud contain expected text */

//    BOOST_CHECK(processorOutput[2].size() == 4);

//    BOOST_CHECK(processorOutput[2][0] ==
//                "main thread - 0 string(s), 0 command(s), 0 bulk(s)");

//    BOOST_CHECK(processorOutput[2][1] ==
//                "log thread - 0 bulk(s), 0 command(s)");
//    BOOST_CHECK(processorOutput[2][2] ==
//                "file thread #0 - 0 bulk(s), 0 command(s)");
//    BOOST_CHECK(processorOutput[2][3] ==
//                "file thread #1 - 0 bulk(s), 0 command(s)");

//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(empty_command_test)
//{
//  const std::string testString{"cmd1\n"
//                               "\n"
//                               "cmd2"};
//  try
//  {
//    auto processorOutput{
//      getProcessorOutput(testString, '{', '}', 3, DebugOutput::debug_off)
//    };

//    /* check main application output */
//    BOOST_CHECK(processorOutput[0][0] == "bulk: cmd1, , cmd2");

//    /* check application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* check application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 3, 3, 1);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(bulk_segmentation_test1)
//{
//  try
//  {
//    const std::string testString{"cmd1\n"
//                           "cmd2\n"
//                           "cmd3\n"
//                           "cmd4"};
//    auto processorOutput{
//      getProcessorOutput(testString, '{', '}', 3, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0].size() == 2);

//    BOOST_CHECK(processorOutput[0][0] == "bulk: cmd1, cmd2, cmd3");
//    BOOST_CHECK(processorOutput[0][1] == "bulk: cmd4");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    if (processorOutput[1].size() != 0)
//    {
//      for (const auto& string : processorOutput[1])
//      {
//        std::cout << string << '\n';
//      }
//    }

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 4, 4, 2);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(bulk_segmentation_test2)
//{
//  try
//  {
//    const std::string testString
//    {
//      "cmd1\n"
//      "<\n"
//      "cmd2\n"
//      "cmd3\n"
//      ">\n"
//      "cmd4"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '<', '>', 3, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0].size() == 3);

//    if (processorOutput[0].size() != 3)
//    {
//      for (const auto& string : processorOutput[0])
//      {
//        std::cout << string << '\n';
//      }
//    }

//    BOOST_CHECK(processorOutput[0][0] == "bulk: cmd1");
//    BOOST_CHECK(processorOutput[0][1] == "bulk: cmd2, cmd3");
//    BOOST_CHECK(processorOutput[0][2] == "bulk: cmd4");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 6, 4, 3);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(nested_bulks_test)
//{
//  try
//  {
//    const std::string testString{
//      "cmd1\n"
//      "cmd2\n"
//      "cmd3\n"
//      "(\n"
//        "cmd4\n"
//        "cmd5\n"
//        "(\n"
//          "cmd6\n"
//          "(\n"
//              "cmd7\n"
//          ")\n"
//          "cmd8\n"
//        ")\n"
//        "cmd9\n"
//      ")\n"
//      "cmd10\n"
//      "cmd11\n"
//      "cmd12\n"
//      "cmd13\n"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '(', ')', 4, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0].size() == 3);
//    BOOST_CHECK(processorOutput[0][0] ==
//                "bulk: cmd1, cmd2, cmd3");
//    BOOST_CHECK(processorOutput[0][1] ==
//                "bulk: cmd4, cmd5, cmd6, cmd7, cmd8, cmd9");
//    BOOST_CHECK(processorOutput[0][2] ==
//                "bulk: cmd10, cmd11, cmd12, cmd13");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 19, 13, 3);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(unexpected_bulk_end_test)
//{
//  try
//  {
//    const std::string testString{
//      "cmd1\n"
//      "cmd2\n"
//      "cmd3\n"
//      "(\n"
//        "cmd4\n"
//        "cmd5\n"
//        "(\n"
//          "cmd6\n"
//          "(\n"
//            "cmd7\n"
//            "cmd8\n"
//          ")\n"
//          "cmd9\n"
//        ")\n"
//        "cmd10\n"
//        "cmd11\n"
//        "cmd12\n"
//        "cmd13\n"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '(', ')', 4, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0][0] ==
//                "bulk: cmd1, cmd2, cmd3");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 18, 3, 1);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(incorrect_closing_test)
//{
//  try
//  {
//    const std::string testString{
//      "cmd1\n"
//      "cmd2\n"
//      "cmd3\n"
//      "(\n"
//        "cmd4\n"
//        "cmd5\n"
//      ")\n"
//      "cmd6\n"
//      ")\n"
//      "cmd7\n"
//      "cmd8\n"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '(', ')', 4, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0][0] ==
//                "bulk: cmd1, cmd2, cmd3");
//    BOOST_CHECK(processorOutput[0][1] ==
//                "bulk: cmd4, cmd5");
//    BOOST_CHECK(processorOutput[0][2] ==
//                "bulk: cmd6, cmd7, cmd8");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 11, 8, 3);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr<< ex.what();
//  }
//}


//BOOST_AUTO_TEST_CASE(commands_containing_delimiter_test)
//{
//  try
//  {
//    const std::string testString
//    {
//      "cmd1\n"
//      "{cmd2\n"
//      "cmd3\n"
//      "cmd4}\n"
//      "cmd5"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '{', '}', 2, DebugOutput::debug_off)
//    };

//    /* main application output */
//    BOOST_CHECK(processorOutput[0][0] == "bulk: cmd1, {cmd2");
//    BOOST_CHECK(processorOutput[0][1] == "bulk: cmd3, cmd4}");
//    BOOST_CHECK(processorOutput[0][2] == "bulk: cmd5");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 5, 5, 3);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}


//BOOST_AUTO_TEST_CASE(logging_test)
//{
//  try
//  {
//    /* wait 2 seconds to get separate log files for this test */
//    std::this_thread::sleep_for(std::chrono::seconds{2});

//    const std::string testString{
//      "cmd1\n"
//      "cmd2\n"
//      "cmd3\n"
//      "cmd4\n"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '(', ')', 4, DebugOutput::debug_off)
//    };

//    /* get current time */
//    std::chrono::time_point<std::chrono::system_clock>
//    bulkStartTime{std::chrono::system_clock::now()};
//    /* convert bulk start time to integer ticks count */
//    auto ticksCount{
//      std::chrono::duration_cast<std::chrono::seconds>
//      (
//        bulkStartTime.time_since_epoch()
//      ).count()
//    };

//    /* build log file name */
//    --ticksCount;
//    while (!std::ifstream{std::to_string(ticksCount).append("_1.log")})
//    {
//      ++ticksCount;
//    }

//    std::string logFileName{
//      std::to_string(ticksCount).append("_1.log")
//    };

//    std::ifstream logFile(logFileName);

//    std::string logString{};
//    std::getline(logFile, logString);

//    /* main application output */
//    BOOST_CHECK(processorOutput[0][0] ==
//                "bulk: cmd1, cmd2, cmd3, cmd4");

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 4, 4, 1);

//    /* check log file state */
//    BOOST_CHECK(logFile);

//    /* check log file content */
//    BOOST_CHECK(logString ==
//                "bulk: cmd1, cmd2, cmd3, cmd4");
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_FAIL("");
//    std::cerr << ex.what();
//  }
//}

//BOOST_AUTO_TEST_CASE(log_file_name_uniqueness_test)
//{
//  try
//  {
//    /* wait 2 seconds to get separate log file for this test */
//    std::this_thread::sleep_for(std::chrono::seconds{2});

//    const std::string testString{
//      "cmd1\n"
//      "cmd2\n"
//      "cmd3\n"
//      "cmd4\n"
//    };
//    auto processorOutput{
//      getProcessorOutput(testString, '(', ')', 1, DebugOutput::debug_off)
//    };

//    /* get current time */
//    std::chrono::time_point<std::chrono::system_clock>
//    bulkStartTime{std::chrono::system_clock::now()};
//    /* convert bulk start time to integer ticks count */
//    auto ticksCount{
//      std::chrono::duration_cast<std::chrono::seconds>
//      (
//        bulkStartTime.time_since_epoch()
//      ).count()
//    };

//    /* build log file name */
//    --ticksCount;
//    while (!std::ifstream{std::to_string(ticksCount).append("_1.log")})
//    {
//      ++ticksCount;
//    }

//    std::string logFileName{};
//    std::ifstream logFile{};
//    std::string logString{};

//    const size_t filesCount{4};

//    for (size_t i{1}; i <= filesCount; ++i)
//    {
//      logFileName = std::to_string(ticksCount) +
//                    + "_" + std::to_string(i) + ".log";

//      logFile.open(logFileName);

//      /* check log file state */
//      BOOST_CHECK(logFile);

//      std::getline(logFile, logString);

//      /* check log file content */
//      BOOST_CHECK(logString ==
//                  "bulk: cmd" + std::to_string(i));

//      logFile.close();
//    }

//    /* main application output */
//    BOOST_CHECK(processorOutput[0].size() == 4);
//    for (size_t i{1}; i <= 4; ++i)
//    {
//      BOOST_CHECK(processorOutput[0][i - 1] ==
//                  "bulk: cmd" + std::to_string(i));
//    }

//    /* application error output */
//    BOOST_CHECK(processorOutput[1].size() == 0);

//    /* application metrics output */
//    BOOST_CHECK(processorOutput[2].size() == 4);

//    std::stringstream metricsStream{};
//    for (const auto& tmpString : processorOutput[2])
//    {
//      metricsStream << tmpString << '\n';
//    }

//    checkMetrics(metricsStream, 4, 4, 4);
//  }
//  catch (const std::exception& ex)
//  {
//    BOOST_CHECK(false);
//    std::cerr << ex.what();
//  }
//}

BOOST_AUTO_TEST_SUITE_END()

