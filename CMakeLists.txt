cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)

add_executable(LogiqueFloue test/main.cpp)

target_link_libraries(LogiqueFloue pthread)
target_link_libraries(LogiqueFloue cppunit)