# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.19)
project(proiektua)

set(CMAKE_C_STANDARD 99)

add_executable(proiektua definetg.h funtg.h funtg_s.c taldegen_s.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-O2 -lm")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")