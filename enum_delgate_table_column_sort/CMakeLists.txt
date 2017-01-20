project(enum_table_sorting)

set(DESIRED_QT_VERSION 5 CACHE STRING "The QT version OpenMW should use (4 or 5)")
message(STATUS "Using Qt${DESIRED_QT_VERSION}")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5OpenGL REQUIRED)
set(CMAKE_AUTOMOC ON)

if (USE_QT)
	# 2.8.11+ is required to make Qt5 happy and allow linking QtMain on Windows.
	cmake_minimum_required(VERSION 2.8.11)
else()
	# We probably support older versions than this.
	cmake_minimum_required(VERSION 2.6)
endif()

# Fix for not visible pthreads functions for linker with glibc 2.15
if (UNIX AND NOT APPLE)
    find_package (Threads)
endif()

# Look for stdint.h
include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)
if(NOT HAVE_STDINT_H)
    unset(HAVE_STDINT_H CACHE)
    message(FATAL_ERROR "stdint.h was not found" )
endif()

include (CheckIncludeFileCXX)
check_include_file_cxx(unordered_map HAVE_UNORDERED_MAP)
if (HAVE_UNORDERED_MAP)
    add_definitions(-DHAVE_UNORDERED_MAP)
endif ()

include_directories("."
    SYSTEM
)

# Set up DEBUG define
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG DEBUG=1)

# CXX Compiler settings
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wno-unused-parameter -std=c++98 -pedantic -Wno-long-long -Wno-deprecated-declarations")

    if (CMAKE_CXX_COMPILER_ID STREQUAL Clang AND NOT APPLE)
        execute_process(COMMAND ${CMAKE_C_COMPILER} --version OUTPUT_VARIABLE CLANG_VERSION)
        string(REGEX REPLACE ".*version ([0-9\\.]*).*" "\\1" CLANG_VERSION ${CLANG_VERSION})
        if ("${CLANG_VERSION}" VERSION_GREATER 3.6 OR "${CLANG_VERSION}" VERSION_EQUAL 3.6)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-potentially-evaluated-expression")
        endif ("${CLANG_VERSION}" VERSION_GREATER 3.6 OR "${CLANG_VERSION}" VERSION_EQUAL 3.6)
    endif(CMAKE_CXX_COMPILER_ID STREQUAL Clang AND NOT APPLE)

    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU AND "${GCC_VERSION}" VERSION_GREATER 4.6 OR "${GCC_VERSION}" VERSION_EQUAL 4.6)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-parameter")
    endif(CMAKE_CXX_COMPILER_ID STREQUAL GNU AND "${GCC_VERSION}" VERSION_GREATER 4.6 OR "${GCC_VERSION}" VERSION_EQUAL 4.6)
endif (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

file(GLOB SOURCE_FILES "*.cpp")
include_directories(${CMAKE_SOURCE_DIR})
message("SOURCE_FILES="${SOURCE_FILES})
find_package(Qt5Core)
find_package(Qt5Widgets)
add_executable(enum_sort ${SOURCE_FILES})
target_link_libraries(enum_sort Qt5::Widgets)
