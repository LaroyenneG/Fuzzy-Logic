cmake_minimum_required(VERSION 3.13)
project(fuzzy-logic)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_ACTIVE_BLACK_BOX_") # enable black box

set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib")

if (LINUX OR UNIX AND NOT APPLE)
    set(CPPUNIT "${LIB_PATH}/libcppunit-unix-64.a")
    set(CPPUNIT cppunit) # mascote
endif ()

if (APPLE)
    message(STATUS ">>> Think different")
endif ()

if (WIN34)
    set(CPPUNIT "${LIB_PATH}/libcppunit-win-64.a")
endif ()


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(lib/include)


################################ Fuzzy logic library ##########################################
include_directories(src/fuzzylogic)
include_directories(src/fuzzylogic/core)
include_directories(src/fuzzylogic/fuzzy)
include_directories(src/fuzzylogic/exception)
include_directories(src/fuzzylogic/interpreter)

file(GLOB_RECURSE CORE_SOURCES src/fuzzylogic/core/*) # all core source files
file(GLOB_RECURSE INTP_SOURCES src/fuzzylogic/interpreter/*) # all interpreter source files
file(GLOB_RECURSE FUZZY_SOURCES src/fuzzylogic/fuzzy/*) # all fuzzy source files
file(GLOB_RECURSE EXCEPTION_SOURCES src/fuzzylogic/exception/*) # all exception source files

set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${INTP_SOURCES} src/fuzzylogic/fuzzylogic.h)

add_library(fuzzylogic ${FUZZY_LIBRARY} lib/include/cppunit/config-auto.h)


############################### Fuzzy logic test ##############################################

file(GLOB_RECURSE FUZZY_TEST_SOURCES test/fuzzylogic/*) # all test source files

add_executable(fuzzylogictest ${FUZZY_TEST_SOURCES} ${FUZZY_LIBRARY})
target_link_libraries(fuzzylogictest "${CPPUNIT}")


################################## Titanic ##############################################

find_package(Qt5 COMPONENTS Core Gui Widgets Xml REQUIRED)
add_definitions(${QT_DEFINITIONS})

include_directories(src/titanic/model)
include_directories(src/titanic/view)
include_directories(src/titanic/controller)


file(GLOB_RECURSE TITANIC_SOURCES src/titanic/model/* src/titanic/view/* src/titanic/controller/*) # all titanic source files

set(INTERFACE_FILES src/titanic/controller/CheckBoxController.h
        src/titanic/controller/SliderController.h
        src/titanic/controller/AutomaticPilotController.h
        src/titanic/controller/TimeWizardController.h
        src/titanic/controller/MenuController.h) # all slots class'

qt5_wrap_cpp(INTERFACE_FILES_MOC ${INTERFACE_FILES})


add_executable(titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY} ${INTERFACE_FILES_MOC} src/titanic/main.cpp)

target_link_libraries(titanic pthread Qt5::Widgets)


##################################### Titanic test #########################################

file(GLOB_RECURSE TITANIC_TEST_SOURCES test/titanic/*) # all test source files

add_executable(titanictest ${TITANIC_SOURCES} ${FUZZY_LIBRARY} ${TITANIC_TEST_SOURCES} ${INTERFACE_FILES_MOC})
target_link_libraries(titanictest pthread Qt5::Widgets "${CPPUNIT}")


################################ Leave a tip ###############################################
include_directories(src/leaveatip)

set(LEAVE_A_TIP_SOURCES src/leaveatip/LeaveATip.cpp src/leaveatip/LeaveATip.h) # all leaveatip source files

add_executable(leaveatip ${LEAVE_A_TIP_SOURCES} ${FUZZY_LIBRARY} src/leaveatip/main.cpp)


################################ Leave a tip test #############################################

file(GLOB_RECURSE TIP_TEST_SOURCES test/leaveatip/*) # all test source files

add_executable(leaveatiptest ${TIP_TEST_SOURCES} ${FUZZY_LIBRARY} ${LEAVE_A_TIP_SOURCES})
target_link_libraries(leaveatiptest "${CPPUNIT}")
