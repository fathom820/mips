cmake_minimum_required(VERSION 3.17.5)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c registers.c registers.h instructions.c instructions.h)
