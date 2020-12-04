# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.19)
project(proiektua)

set(CMAKE_C_STANDARD 99)

add_executable(proiektua definetg.h funtg.h funtg_s.c taldegen_s.c)
