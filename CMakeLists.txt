cmake_minimum_required(VERSION 3.5)

project (dailyLeetCode)

aux_source_directory(./leetcode DIR_SRCS)

add_executable(dailyLeetCode ${DIR_SRCS})
find_package(GTest CONFIG REQUIRED)
target_link_libraries(dailyLeetCode PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)