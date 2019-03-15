cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -g")

message(STATUS "Find Qt5")
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)


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
file(GLOB_RECURSE TITANIC_SOURCES titanic/*) # all titanic source files


set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${GUI_SOURCES})

add_library(fuzzy ${FUZZY_LIBRARY})
add_executable(FuzzyTest ${TEST_SOURCES} ${FUZZY_LIBRARY})
add_executable(Titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY})

if (UNIX)
    set(CPPUNIT libcppunit-unix-64.a)
    message(STATUS "OS >>> UNIX")
elseif (WIN32)
    set(CPPUNIT libcppunit-win-64.a)
    message(STATUS "OS >>> WINDOWS")
endif ()

set(QT_MODULES Qt5::Widgets Qt5::Core)

message(STATUS "Add libraries...")

target_link_libraries(FuzzyTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT})
target_link_libraries(FuzzyTest ${QT_MODULES})
target_link_libraries(Titanic ${QT_MODULES})

message("Cppunit archive file : ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT}")