#ifndef ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
#define ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H

#include "LinearRegression.h"
#include <chrono>

using namespace std::chrono;
using std::cout;
using std::endl;

void testInverseGaussJordan(ComplexMatrix<double> Matrix) {
    Matrix.getInverseGaussJordan();
}

void testInverseLU(ComplexMatrix<double> Matrix) {
    Matrix.getInverseLU();
}

void testStrassenAlgorithm(ComplexMatrix<double> Matrix) {
    Matrix * Matrix;
}

void testBuildingLinearRegression(ComplexMatrix<double> Y, ComplexMatrix<double> X) {
    buildLinearRegression(Y, X);
}

void timeTestInverseGaussJordan(int order = 10)
{
    int accuracy = 100;
    cout << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < accuracy; ++i) {
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order);
        testInverseGaussJordan(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму інверсії методом Жордана-Гауса: ";
    cout << res / 1000000 << " секунд, "
         << res % 1000000 / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestInverseLU(int order = 10)
{
    int accuracy = 100;
    cout << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < accuracy; ++i) {
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order);
        testInverseLU(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму інверсії LU розкладанням: ";
    cout << res / 1000000 << " секунд, "
         << res % 1000000 / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestStrassenAlgorithm(int rows = 10, int columns = 10)
{
    int accuracy = 100;
    cout << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < accuracy; ++i) {
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(rows, columns);
        testStrassenAlgorithm(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму Штрассена: ";
    cout << res / 1000000 << " секунд, "
         << res % 1000000 / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeLinearRegression(int varsAmount = 5, int dataAmount = 10) {
    int accuracy = 100;
    cout << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < accuracy; ++i) {
        ComplexMatrix<double> Y = ComplexMatrix<double>::getRandom(dataAmount, 1);
        ComplexMatrix<double> X = ComplexMatrix<double>::getRandom(dataAmount, varsAmount);
        testBuildingLinearRegression(Y, X);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму побудови лінійної регресії: ";
    cout << res / 1000000 << " секунд, "
         << res % 1000000 / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

#endif //ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
