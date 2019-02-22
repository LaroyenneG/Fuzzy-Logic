# please keep out !

cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")


include_directories(src/core)
include_directories(src/fuzzy)

file(GLOB_RECURSE CORE_SOURCES src/core/*) # all core source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE TEST_SOURCES test/* test/core/* test/fuzzy/*) # all test source files


add_executable(LogiqueFloueTest ${TEST_SOURCES} ${CORE_SOURCES} ${FUZZY_SOURCES})

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest cppunit)
