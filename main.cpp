#include "Complex.h"
#include "ComplexMatrix.h"
#include "LU.h"
#include <ctime>

using std::vector;
using std::cout;
using std::endl;

int main()
{
    // Order of the matrix.
    int order = 3;
    // The matrix must be a square a matrix.
    /*
    float matrix[20][20] = { { 5, 7, 9 },
                             { 4, 3, 8 },
                             { 7, 5, 6 } };
*/
    /*ComplexMatrix<float> identity = ComplexMatrix<float>::getIdentity(order);
    cout << "~~~ Matrix ~~~\n";
    identity.print();
    identity = identity.getInverseGaussJordan();

    cout << "\n~~~ Inverse Matrix ~~~\n";
    identity.print();
    cout << clock() << "ms";
    return 0;
     */

    int N = 3;

    ComplexMatrix<float> matrix(N), inverse(N), lower(N), upper(N), z(N), i(N);
    matrix = matrix.fill();

    LU lu(matrix, inverse, lower, upper, z, i, N);
    lu.run();

    return 0;
}