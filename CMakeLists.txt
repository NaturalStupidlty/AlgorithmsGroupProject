cmake_minimum_required(VERSION 3.20)
project(AlgorithmsGroupProjectLU)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AlgorithmsGroupProjectLU
        Headers/Complex.h
        Headers/ComplexMatrix.h
        main.cpp
        Headers/Errors.h
        Headers/LinearRegression.h
        Headers/doctest.h "Unit tests/Test getInverseGaussJordan.cpp")
