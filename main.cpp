#include "Complex.h"
#include "ComplexMatrix.h"
// Пізніше може знадобитися для бенчмаркінгу
//#include <ctime>

using std::vector;
using std::cout;
using std::endl;

int main() {
    int N = 3;
    ComplexMatrix<float> m = ComplexMatrix<float>(N);
    m[0][0] = Complex<float>(1, 9);
    m[0][1] = Complex<float>(2, 8);
    m[0][2] = Complex<float>(3, -7);
    m[1][0] = Complex<float>(4, 6);
    m[1][1] = Complex<float>(5, 5);
    m[1][2] = Complex<float>(6, 4);
    m[2][0] = Complex<float>(-7, 3);
    m[2][1] = Complex<float>(8, 2);
    m[2][2] = Complex<float>(9, 1);

    ComplexMatrix<float> matrix(N), inverse(N), lower(N), upper(N), z(N), i(N);
    matrix = ComplexMatrix<float>::getRandom(N);
    m.getInverseGaussJordan().print();
    matrix.getInverseLU().print();
    return 0;
}
