#ifndef ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
#define ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H

#include "Headers/ComplexMatrix.h"
#include "LinearRegression.h"
#include <chrono>

using namespace std::chrono;
using std::cout;
using std::endl;

void testInverseGaussJordan(ComplexMatrix<double> Matrix) {
    Matrix.getInverse("Gauss-Jordan");
}

void testInverseLU(ComplexMatrix<double> Matrix) {
    Matrix.getInverse("LU");
}

void testStrassenAlgorithm(ComplexMatrix<double> Matrix) {
    Matrix.StrassenMultiply(Matrix);
}

void testRegularMultiplication(ComplexMatrix<double> Matrix) {
    Matrix * Matrix;
}

void testBuildingLinearRegression(const ComplexMatrix<double>& Y, const ComplexMatrix<double>& X) {
    LinearRegression<double> regression(Y, X);
}

void timeTestInverseGaussJordan(int order = 10, int accuracy = 100)
{
    cout << endl;
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    for (int i = 0; i < accuracy; ++i) {
        creationStart = high_resolution_clock::now();
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order, order);
        creationStop = high_resolution_clock::now();
        start -= (creationStart - creationStop);
        testInverseGaussJordan(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count() / accuracy;
    cout << "Середній час виконання алгоритму інверсії методом Жордана-Гауса: ";
    cout << res / 1000000 << " секунд, "
         << (res % 1000000) / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestInverseLU(int order = 10, int accuracy = 100)
{
    cout << endl;
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    for (int i = 0; i < accuracy; ++i) {
        creationStart = high_resolution_clock::now();
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order, order);
        creationStop = high_resolution_clock::now();
        start -= (creationStart - creationStop);
        testInverseLU(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму інверсії LU розкладанням: ";
    cout << res / 1000000 << " секунд, "
         << (res % 1000000) / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestStrassenAlgorithm(int rows = 10, int columns = 10, int accuracy = 100)
{
    cout << endl;
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    for (int i = 0; i < accuracy; ++i) {
        creationStart = high_resolution_clock::now();
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(rows, columns);
        creationStop = high_resolution_clock::now();
        start -= (creationStart - creationStop);
        testStrassenAlgorithm(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму Штрассена: ";
    cout << res / 1000000 << " секунд, "
         << (res % 1000000) / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestRegularMultiplication(int rows = 10, int columns = 10, int accuracy = 100)
{
    cout << endl;
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    for (int i = 0; i < accuracy; ++i) {
        ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(rows, columns);
        testRegularMultiplication(Test);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму звичайного множення: ";
    cout << res / 1000000 << " секунд, "
         << (res % 1000000) / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeLinearRegression(int varsAmount = 5, int dataAmount = 10, int accuracy = 100) {
    cout << endl;
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    for (int i = 0; i < accuracy; ++i) {
        creationStart = high_resolution_clock::now();
        ComplexMatrix<double> Y = ComplexMatrix<double>::getRandom(dataAmount, 1);
        ComplexMatrix<double> X = ComplexMatrix<double>::getRandom(dataAmount, varsAmount);
        creationStop = high_resolution_clock::now();
        start -= (creationStart - creationStop);
        testBuildingLinearRegression(Y, X);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count()/accuracy;
    cout << "Середній час виконання алгоритму побудови лінійної регресії: ";
    cout << res / 1000000 << " секунд, "
         << (res % 1000000) / 1000 << " мілісекунд i "
         << res % 1000 << " мікросекунд" << endl;
    cout << endl;
}

#endif //ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
