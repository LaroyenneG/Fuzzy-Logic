cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")

if (UNIX)
    set(CPPUNIT libcppunit-unix-64.a)
elseif (WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.12.2\\mingw73_64")
    set(CPPUNIT libcppunit-win-64.a)
endif ()

message(STATUS "Find Qt5")
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5WebKit CONFIG REQUIRED)


message(STATUS "Sources directory :  ${CMAKE_SOURCE_DIR}")

include_directories(lib/include)

include_directories(src/core)
include_directories(src/fuzzy)
include_directories(src/exception)
include_directories(src/interpreter)

file(GLOB_RECURSE CORE_SOURCES src/core/*) # all core source files
file(GLOB_RECURSE INTP_SOURCES src/interpreter/*) # all interpreter source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE EXCEPTION_SOURCES src/exception/*) # all exception source files

file(GLOB_RECURSE TEST_SOURCES test/* test/core/* test/fuzzy/*) # all test source files
file(GLOB_RECURSE TITANIC_SOURCES titanic/*) # all titanic source files


set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${INTP_SOURCES})

add_library(fuzzy ${FUZZY_LIBRARY})
add_executable(FuzzyTest ${TEST_SOURCES} ${FUZZY_LIBRARY})
add_executable(Titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY})

set(QT_MODULES Qt5::Widgets Qt5::Core)

message(STATUS "Add libraries...")

target_link_libraries(FuzzyTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT})
target_link_libraries(FuzzyTest ${QT_MODULES})
target_link_libraries(Titanic ${QT_MODULES})

message("Cppunit archive file : ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT}")