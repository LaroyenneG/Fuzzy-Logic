# please keep out !

cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")

set(CORE_PATH src/core)
set(FUZZY_PATH src/fuzzy)
set(TEST_PATH test)

include_directories(src/core)
include_directories(src/fuzzy)

file(GLOB_RECURSE CORE_SOURCES ${CORE_PATH}/*) # all core source files
file(GLOB_RECURSE FUZZY_SOURCES ${FUZZY_PATH}/*) # all fuzzy source files
file(GLOB_RECURSE TEST_SOURCES ${TEST_PATH}/*) # all test source files


add_executable(LogiqueFloueTest ${TEST_SOURCES} ${CORE_SOURCES} ${FUZZY_SOURCES})

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest cppunit)
