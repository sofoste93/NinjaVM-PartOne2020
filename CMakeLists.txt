cmake_minimum_required(VERSION 3.17)
project(NinjaVM_PartOne2020 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(NinjaVM_PartOne2020
        header.h unixshell.h njvm4.c njvm4.h)
