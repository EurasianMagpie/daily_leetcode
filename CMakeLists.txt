cmake_minimum_required(VERSION 3.5)

project (dailyLeetCode)

aux_source_directory(./leetcode DIR_SRCS)

add_executable(dailyLeetCode ${DIR_SRCS})
find_package(gtest REQUIRED)
include_directories(${gtest_INCLUDE_DIRS})
target_link_libraries(dailyLeetCode ${gtest_LIBS})