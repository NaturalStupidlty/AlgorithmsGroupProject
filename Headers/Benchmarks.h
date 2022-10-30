#ifndef ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
#define ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H

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

void timeTestInverseGaussJordan(int order = 10)
{
    ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order, order);
    cout << endl;
    auto start = high_resolution_clock::now();
    testInverseGaussJordan(Test);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Обернена матриця методом Жордана-Гауса: " << endl;
    cout << "Час виконання для матриці розмірності " << Test.getRows()
    << "x" << Test.getColumns() << ":" << endl;
    cout << duration.count() / 1000000 << " секунд, "
         << duration.count() / 1000 << " мілісекунд i "
         << duration.count() % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestInverseLU(int order = 10)
{
    ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(order, order);
    cout << endl;
    auto start = high_resolution_clock::now();
    testInverseLU(Test);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Обернена матриця методом LU-розкладу: " << endl;
    cout << "Час виконання для матриці розмірності " << Test.getRows()
    << "x" << Test.getColumns() << ":" << endl;
    cout << duration.count() / 1000000 << " секунд, "
         << duration.count() / 1000 << " мілісекунд i "
         << duration.count() % 1000 << " мікросекунд" << endl;
    cout << endl;
}

void timeTestStrassenAlgorithm(int rows = 10, int columns = 10)
{
    ComplexMatrix<double> Test = ComplexMatrix<double>::getRandom(rows, columns);
    cout << endl;
    auto start = high_resolution_clock::now();
    testStrassenAlgorithm(Test);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Множення матриць алгоритмом Штрассена: " <<  endl;
    cout << "Час виконання для матриці розмірності " << Test.getRows()
    << "x" << Test.getColumns() << ":" << endl;
    cout << duration.count() / 1000000 << " секунд, "
         << duration.count() / 1000 << " мілісекунд i "
         << duration.count() % 1000 << " мікросекунд" << endl;
    cout << endl;
}

#endif //ALGORITHMSGROUPPROJECTLU_BENCHMARKS_H
