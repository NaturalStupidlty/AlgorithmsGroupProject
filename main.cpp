#include "Complex.h"
#include "ComplexMatrix.h"
// Для бенчмаркінгу
#include <chrono>
#include <vector>

using namespace std::chrono;
using std::vector;
using std::cout;
using std::endl;

int main() {
    int N = 3, M = 3;

    ComplexMatrix<float> m = ComplexMatrix<float>(N, M);
    m[0][0] = Complex<float>(1, 9);
    m[0][1] = Complex<float>(2, 8);
    m[0][2] = Complex<float>(3, -7);
    m[1][0] = Complex<float>(4, 6);
    m[1][1] = Complex<float>(5, 5);
    m[1][2] = Complex<float>(6, 4);
    m[2][0] = Complex<float>(-7, 3);
    m[2][1] = Complex<float>(8, 2);
    m[2][2] = Complex<float>(9, 1);


    ComplexMatrix<float> m4(3);
    m4[0][0] = Complex<float>(0);
    m4[0][1] = Complex<float>(0);
    m4[0][2] = Complex<float>(0);

    m4[1][0] = Complex<float>(2);
    m4[1][1] = Complex<float>(88);
    m4[1][2] = Complex<float>(42);

    m4[2][0] = Complex<float>(1);
    m4[2][1] = Complex<float>(6);
    m4[2][2] = Complex<float>(1);


    m4.getInverseGaussJordan().print();
    m4.getInverseLU().print();

    // бенчмаркінг
/*    auto start = high_resolution_clock::now();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;*/

    return 0;
}
