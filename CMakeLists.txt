cmake_minimum_required(VERSION 3.20)
project(AlgorithmsGroupProjectLU)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AlgorithmsGroupProjectLU
        Headers/Complex.h
        Headers/ComplexMatrix.h
        Cpp/main.cpp
        Headers/Errors.h
        Headers/LinearRegression.h
        Headers/Doctest/doctest.h
        "Cpp/Unit tests/Test getInverseGaussJordan.cpp"
        "Cpp/Unit tests/Test Linear Regression.cpp"
        "Cpp/Unit tests/Test getInverseLU.cpp"
        "Cpp/Unit tests/Test Strassen Algorithm.cpp"
        Headers/Benchmarks.h)
