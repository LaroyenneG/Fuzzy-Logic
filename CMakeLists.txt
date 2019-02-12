cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)


set(sources src/core/BinaryExpression.cpp src/core/BinaryExpression.h) # all projet source files


# please keep out !

include_directories(src/core)
include_directories(src/fuzzy)

add_executable(
        LogiqueFloueTest
        test/main.cpp
        ${sources})

add_library(
        LogiqueFloue
        ${sources}
)

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest cppunit)