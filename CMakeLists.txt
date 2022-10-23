cmake_minimum_required(VERSION 3.20)
project(AlgorithmsGroupProjectLU)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AlgorithmsGroupProjectLU
        Complex.h
        ComplexMatrix.h
        main.cpp
        Errors.h)
