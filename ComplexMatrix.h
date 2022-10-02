#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include <vector>
#include "Complex.h"

using std::vector;
using std::cout;

template <typename T> class ComplexMatrix
{
private:
    int N;
    vector<vector<Complex<T>>> matrix;
public:
    // Create NxN matrix of zeroes
    explicit ComplexMatrix(int N)
    {
        this->N = N;
        for (int i = 0; i < N; ++i)
        {
            vector<Complex<T>> line;
            for (int j = 0; j < N; ++j)
            {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    // Function to print out the matrix
    void print()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                matrix[i][j].print();
            }
            cout << endl;
        }
    }

    // !!!
    Complex<T> operator [] (const int& i)
    {

    }

    // !!!

    // Function to perform the inverse operation on the matrix
    ComplexMatrix<T> getInverse()
    {
        // Create an identity matrix
        ComplexMatrix<T> identity = getIdentity();


        // Interchange the row of matrix,
        // interchanging of row will start from the last row.
        for (int i = order - 1; i > 0; i--)
        {
            // Directly swapping the rows using pointers saves time.
            if (matrix[i][0] > matrix[i - 1][0])
            {
                swap(matrix[i], matrix[i - 1]);
                swap(identity[i], identity[i - 1]);
            }
        }

        // Replace a row by sum of itself and a
        // constant multiple of another row of the matrix.
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                if (j != i)
                {
                    Complex<T> temp = matrix[j][i].divide(matrix[j][i], matrix[i][i]);
                    for (int k = 0; k < order; k++)
                    {
                        matrix[j][k] = matrix[j][k].subtract(matrix[j][k], matrix[j][k].multiply(matrix[i][k], temp));
                        identity[j][k] = identity[j][k].subtract(identity[j][k], identity[i][k].multiply(identity[i][k], temp));
                    }
                }
            }
        }

        // Multiply each row by a nonzero integer.
        // Divide row element by the diagonal element
        for (int i = 0; i < order; i++)
        {
            Complex<T> temp = matrix[i][i];
            for (int j = 0; j < order; j++)
            {
                matrix[i][j] = matrix[i][j].divide(matrix[i][j], temp);
                identity[i][j] = identity[i][j].divide(identity[i][j], temp);
            }
        }

        return identity;
    }

};

// Get identity matrix of the same order
template <typename T> ComplexMatrix<T> getIdentity(int N)
{
    ComplexMatrix<T> identity;
    identity.N = N;
    for (int i = 0; i < N; ++i)
    {
        vector<Complex<T>> line;
        for (int j = 0; j < N; ++j)
        {
            Complex<T> number;
            if (i == j)
            {
                number.real = 1;
            }
            line.push_back(number);
        }
        identity.push_back(line);
    }
    return identity;
}

#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
