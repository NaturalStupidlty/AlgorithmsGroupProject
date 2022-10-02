#include "Complex.h"
#include "ComplexMatrix.h"

using std::vector;

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
    ComplexMatrix<float> matrix = getIdentity<float>(order);

    cout << "~~~ Matrix ~~~\n";
    matrix.print();

    matrix = matrix.getInverse();

    cout << "\n~~~ Inverse Matrix ~~~\n";
    matrix.print();
    return 0;
}