cmake_minimum_required(VERSION 3.13)
project(CPE446Lab2 C)

set(CMAKE_C_STANDARD 99)
#add_compile_definitions(PRINT)

add_executable(CPE446Lab2 main.c parity.c parity.h main.h hamming.c hamming.h util.c util.h matrix.h matrix.c)