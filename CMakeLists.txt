cmake_minimum_required(VERSION 3.25)
project(takokb C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-O0 -g)
endif ()

add_definitions(-DTAKOKB_MAX_LAYERS=4)
add_definitions(-DTAKOKB_MATRIX_ROWS=2)
add_definitions(-DTAKOKB_MATRIX_COLS=8)
add_definitions(-DTAKOKB_TEST)

include_directories(src inc test)
file(GLOB_RECURSE SOURCES src/*.*)
file(GLOB_RECURSE TEST_SOURCES test/common.c)

enable_testing()
add_executable(test_key_press ${SOURCES} ${TEST_SOURCES} test/1_key_press.cpp)

add_test(NAME key_press COMMAND test_key_press)
