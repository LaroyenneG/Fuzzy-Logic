cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _ACTIVE_BLACK_BOX_") # enable black box

if (LINUX OR UNIX AND NOT APPLE)
    set(CPPUNIT libcppunit-unix-64.a)
endif ()

if (APPLE)
    message(STATUS ">>> Think different")
endif ()

if (WIN32)
    set(CPPUNIT libcppunit-win-64.a)
endif ()


find_package(Qt5Widgets CONFIG REQUIRED)
add_definitions(${QT_DEFINITIONS})
set(QT_USE_QTOPENGL TRUE)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(lib/include)

include_directories(src/fuzzylogic)
include_directories(src/fuzzylogic/core)
include_directories(src/fuzzylogic/fuzzy)
include_directories(src/fuzzylogic/exception)
include_directories(src/fuzzylogic/interpreter)

include_directories(src/titanic/model)
include_directories(src/titanic/view)
include_directories(src/titanic/controller)
include_directories(src/titanic/helper)

file(GLOB_RECURSE CORE_SOURCES src/fuzzylogic/core/*) # all core source files
file(GLOB_RECURSE INTP_SOURCES src/fuzzylogic/interpreter/*) # all interpreter source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzylogic/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE EXCEPTION_SOURCES src/fuzzylogic/exception/*) # all exception source files
file(GLOB_RECURSE TEST_SOURCES test/* test/fuzzylogic/core/* test/fuzzylogic/fuzzy/*) # all test source files
file(GLOB_RECURSE TITANIC_SOURCES src/titanic/* src/titanic/model/* src/titanic/view/* src/titanic/controller/*) # all titanic source files

set(INTERFACE_FILES src/titanic/controller/CheckBoxController.h
        src/titanic/controller/SliderController.h
        src/titanic/controller/AutomaticPilotController.h
        src/titanic/controller/TimeWizardController.h
        src/titanic/controller/MenuController.h) # all slots class'

qt5_wrap_cpp(INTERFACE_FILES_MOC ${INTERFACE_FILES})

set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${INTP_SOURCES} src/fuzzylogic/fuzzylogic.h)

add_library(fuzzylogic ${FUZZY_LIBRARY})
add_executable(FuzzyTest ${TEST_SOURCES} ${FUZZY_LIBRARY})
add_executable(Titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY} ${INTERFACE_FILES_MOC})


# Library link

# target_link_libraries(FuzzyTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT}) # <= because mascot
target_link_libraries(FuzzyTest cppunit)

target_link_libraries(Titanic Qt5::Widgets)
target_link_libraries(Titanic pthread)
