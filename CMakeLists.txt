cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -g -D _ACTIVE_BLACK_BOX_")


set(CPPUNIT libcppunit-unix-64.a)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
SET(QT_USE_QTOPENGL TRUE)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "Sources directory :  ${CMAKE_SOURCE_DIR}")

include_directories(lib/include)

include_directories(src/core)
include_directories(src/fuzzy)
include_directories(src/exception)
include_directories(src/interpreter)

include_directories(titanic/model)
include_directories(titanic/view)
include_directories(titanic/controller)
include_directories(titanic/helper)

file(GLOB_RECURSE CORE_SOURCES src/core/*) # all core source files
file(GLOB_RECURSE INTP_SOURCES src/interpreter/*) # all interpreter source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE EXCEPTION_SOURCES src/exception/*) # all exception source files

file(GLOB_RECURSE TEST_SOURCES test/* test/core/* test/fuzzy/*) # all test source files

file(GLOB_RECURSE TITANIC_SOURCES titanic/* titanic/model/* titanic/view/* titanic/controller/*) # all titanic source files

set(INTERFACE_FILES titanic/controller/CheckBoxController.h
        titanic/controller/SliderController.h
        titanic/controller/AutomaticPilotController.h
        titanic/controller/TimeWizardController.h
        titanic/controller/MenuController.h) # all slots class'

QT4_WRAP_CPP(INTERFACE_FILES_MOC ${INTERFACE_FILES})

set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${INTP_SOURCES})

add_library(fuzzy ${FUZZY_LIBRARY})
add_executable(FuzzyTest ${TEST_SOURCES} ${FUZZY_LIBRARY})
add_executable(Titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY} ${INTERFACE_FILES_MOC})


# target_link_libraries(FuzzyTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT})
target_link_libraries(FuzzyTest cppunit)
target_link_libraries(Titanic ${QT_LIBRARIES})
target_link_libraries(Titanic pthread)

message("Cppunit archive file : ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT}")