cmake_minimum_required(VERSION 3.20)
project("lfucache")

add_executable(lfu main.cpp)

include(CTest)
enable_testing()

add_executable(tests e2e.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)


target_link_libraries(tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)

