cmake_minimum_required(VERSION 3.12)

# External libraries
include(pico_sdk_import.cmake)
include(libxy_import.cmake)

# Project
project(retro_console_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pico Standard Library
pico_sdk_init()

# Controller Library
add_subdirectory(src/libcontrollers/)
include_directories(src/libcontrollers/)

# Game Libraries
add_subdirectory(src/pong)
add_subdirectory(src/asteroids)

# Main source
add_executable(main src/main.c)
pico_add_extra_outputs(main)

# Linkage
target_link_libraries(main
    ${LIB_XY_LINK}
    controllers

    pong
    asteroids

    pico_stdlib
    pico_multicore
    pico_rand
)
