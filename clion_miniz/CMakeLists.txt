cmake_minimum_required(VERSION 3.27)
project(clion_miniz C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(clion_miniz
        main.c
        miniz.c
        miniz.h)
