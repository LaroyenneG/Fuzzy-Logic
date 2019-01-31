cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/core)

add_executable(LogiqueFloue test/main.cpp src/core/BinaryExpression.cpp src/core/BinaryExpression.h)

target_link_libraries(LogiqueFloue pthread)
target_link_libraries(LogiqueFloue cppunit)