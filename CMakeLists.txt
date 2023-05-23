cmake_minimum_required(VERSION 3.25)
project(takokb C)

set(CMAKE_C_STANDARD 11)

add_definitions(-DMAX_LAYERS=8)
add_definitions(-DMATRIX_ROWS=3)
add_definitions(-DMATRIX_COLS=4)
add_definitions(-DTAKOKB_TEST)

include_directories(src inc test)
file(GLOB_RECURSE SOURCES src/*.*)
file(GLOB_RECURSE TEST_SOURCES test/common.c)

enable_testing()
add_executable(test_key_press ${SOURCES} ${TEST_SOURCES} test/key_press.c)

add_test(NAME key_press COMMAND test_key_press)
