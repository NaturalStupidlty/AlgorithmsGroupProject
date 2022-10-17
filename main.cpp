#include "Complex.h"
#include "ComplexMatrix.h"
#include "LU.h"
// Пізніше може знадобитися для бенчмаркінгу
//#include <ctime>

using std::vector;
using std::cout;
using std::endl;

int main() {
    int N = 3;

    ComplexMatrix<float> matrix(N), inverse(N), lower(N), upper(N), z(N), i(N);
    matrix = ComplexMatrix<float>::createRandom(N);

    ComplexMatrix<float> m = ComplexMatrix<float>::getIdentity(N);

    m[0][1] = Complex<float>(2, 0);
    m[0][2] = Complex<float>(3, 0);
    m[1][0] = Complex<float>(4, 0);
    m[1][1] = Complex<float>(5, 0);
    m[1][2] = Complex<float>(6, 0);
    m[2][0] = Complex<float>(-7, 0);
    m[2][1] = Complex<float>(8, 0);
    m[2][2] = Complex<float>(9, 0);

    m.getInverseGaussJordan().print();


    LU lu(m, inverse, lower, upper, z, i, N);
    lu.run();

    return 0;
}
