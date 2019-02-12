cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/core)
include_directories(src/fuzzy)

add_executable(
        LogiqueFloueTest
        test/main.cpp
        src/core/BinaryExpression.cpp
        src/core/BinaryExpression.h)

add_library(
        LogiqueFloue
        src/core/BinaryExpression.cpp
        src/core/BinaryExpression.h)

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest cppunit)