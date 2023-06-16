cmake_minimum_required(VERSION 3.21)
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

set(HEADERS "inc/takokb.h" "inc/takokb_action.h")

# Library
file(GLOB_RECURSE SOURCES src/*.*)

add_library(${PROJECT_NAME})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install
install(TARGETS "${PROJECT_NAME}"
        EXPORT "${PROJECT_NAME}-target"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

if (NOT CMAKE_CROSSCOMPILING)
    enable_testing()

    function(add_test_executable name)
        add_executable(${name} test/common.c test/${name}.cpp)
        target_link_libraries(${name} PRIVATE takokb)
        target_include_directories(${name} PRIVATE src)
        target_compile_definitions(${name} PRIVATE -DTAKOKB_MAX_LAYERS=4)
        target_compile_definitions(${name} PRIVATE -DTAKOKB_MATRIX_ROWS=1)
        target_compile_definitions(${name} PRIVATE -DTAKOKB_MATRIX_COLS=4)
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    add_test_executable(0_size)
    add_test_executable(1_key_press)
    add_test_executable(2_layer)
    add_test_executable(3_layer_toggle)
    add_test_executable(4_bottom_layer)
    add_test_executable(5_tap_key_hold_layer)
    add_test_executable(6_configurator_get_version)
endif ()
