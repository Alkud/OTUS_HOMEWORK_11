#CmakeList.txt for OTUS Homework #10

#Check CMake version
cmake_minimum_required(VERSION 3.2)

#Set project name, set PROJECT_VERSION_MINOR value equal to TRAVIS_BUILD NUMBER
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set (VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})
else ()
  set (VERSION_PATCH 1)
endif()

set(CMAKE_CXX_STANDARD 14)

project(async VERSION 0.0.${VERSION_PATCH})

#add library subdirectory
add_subdirectory(async_command_processor)

set (BOOST_MIN_VERSION "1.54.0")

#Find Boost UTF component, get BOOST_LIBRARIES and BOOST_INCLUDE_DIR values
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(BOOST_DEBUG                ON)
set(Boost_USE_MULTITHREADED    ON)


set(homework_11
    ${PROJECT_SOURCE_DIR}/homework_11.h
    ${PROJECT_SOURCE_DIR}/homework_11.cpp)

#Set executable target
add_executable(bulkasync bulkasync.cpp ${homework_11})

#Set test target_link_libraries
add_executable(otus_hw_11_test otus_hw_11_test.cpp ${homework_11} new_delete.h)

add_executable(test4 test4.cpp)

#Enable tests
enable_testing()
add_test(NAME test_hw_11
         COMMAND otus_hw_11_test)

#Set properties and compile options for executable target
set_target_properties(bulkasync
                      PROPERTIES CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#Set properties for test target
set_target_properties(otus_hw_11_test PROPERTIES
                      COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
                      INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(async PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(test4
                      PROPERTIES CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#Link
target_link_libraries(bulkasync async)

target_link_libraries(otus_hw_11_test async)

target_link_libraries(otus_hw_11_test
                      ${Boost_LIBRARIES})

target_link_libraries(test4 async)

