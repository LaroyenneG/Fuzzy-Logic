cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")

set(SOURCES src/core/BinaryExpression.h src/core/Expression.h src/core/UnaryExpression.h) # all projet source files


# please keep out !

include_directories(src/core)
include_directories(src/fuzzy)

add_executable(
        LogiqueFloueTest
        test/main.cpp
        ${SOURCES})

add_library(
        LogiqueFloue
        ${SOURCES}
)

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest cppunit)