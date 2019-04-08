cmake_minimum_required(VERSION 3.13)
project(LogiqueFloue)

option(BLACK_BOX "Enable black box mode" ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -g")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _ACTIVE_BLACK_BOX_") # enable black box


set(CPPUNIT libcppunit-unix-64.a)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(QT_USE_QTOPENGL TRUE)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

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

qt4_wrap_cpp(INTERFACE_FILES_MOC ${INTERFACE_FILES})

set(FUZZY_LIBRARY ${CORE_SOURCES} ${FUZZY_SOURCES} ${EXCEPTION_SOURCES} ${INTP_SOURCES})

add_library(fuzzy ${FUZZY_LIBRARY})
add_executable(FuzzyTest ${TEST_SOURCES} ${FUZZY_LIBRARY})
add_executable(Titanic ${TITANIC_SOURCES} ${FUZZY_LIBRARY} ${INTERFACE_FILES_MOC})


# target_link_libraries(FuzzyTest ${CMAKE_SOURCE_DIR}/lib/${CPPUNIT})
target_link_libraries(FuzzyTest cppunit)
target_link_libraries(Titanic ${QT_LIBRARIES})
target_link_libraries(Titanic pthread)
