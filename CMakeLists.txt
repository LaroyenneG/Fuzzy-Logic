cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")

message(STATUS "Find Qt5")
find_package(Qt5Widgets CONFIG REQUIRED)

message(STATUS "Sources directory :  ${CMAKE_SOURCE_DIR}")

include_directories(lib/include)

include_directories(src/core)
include_directories(src/fuzzy)
include_directories(src/exception)
include_directories(src/gui)

file(GLOB_RECURSE CORE_SOURCES src/core/*) # all core source files
file(GLOB_RECURSE GUI_SOURCES src/gui/*) # all gui source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE EXCEPTION_SOURCES src/exception/*) # all exception source files
file(GLOB_RECURSE TEST_SOURCES test/* test/core/* test/fuzzy/*) # all test source files

add_executable(LogiqueFloueTest ${TEST_SOURCES} ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${GUI_SOURCES})

if (UNIX)
    set(CPPUNIT libcppunit-unix-64.a)
    message(STATUS "OS >>> UNIX")
elseif (WIN32)
    set(CPPUNIT libcppunit-win-64.a)
    message(STATUS "OS >>> WINDOWS")
endif ()

message(STATUS "Add libraries...")

target_link_libraries(LogiqueFloueTest pthread)
target_link_libraries(LogiqueFloueTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT})
target_link_libraries(LogiqueFloueTest Qt5::Widgets)

message("Cppunit archive file : ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT}")