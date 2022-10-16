#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include <vector>
#include "Complex.h"

using std::vector;
using std::cout;
using std::swap;

template <typename T> class ComplexMatrix
{
private:
    int order{};
    vector<vector<Complex<T>>> matrix;
public:
    // Doesn't work correctly
    // [] overloading
    vector<Complex<T>>& operator [] (const int& i)
    {
        return this->matrix[i];
    }

    // Create NxN matrix of zeroes
    explicit ComplexMatrix(int N)
    {
        this->order = N;
        for (int i = 0; i < order; ++i)
        {
            vector<Complex<T>> line;
            for (int j = 0; j < order; ++j)
            {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    static ComplexMatrix<T> getIdentity(int N)
    {
        ComplexMatrix<T> identity(N);
        for (int i = 0; i < N; ++i)
        {
            identity[i][i].real = 1;
        }
        return identity;
    }

    ComplexMatrix<T> fill()
    {
        ComplexMatrix<T> F(3);
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < order; ++j) {
                F[i][j] = Complex<float>(rand(), rand());
            }
        }
        return F;
    }

    // Function to perform the inverse operation on the matrix
    ComplexMatrix<T> getInverseGaussJordan()
    {
        // Create an identity matrix
        ComplexMatrix<T> identity = ComplexMatrix<T>::getIdentity(this->order);


        // Interchange the row of matrix,
        // interchanging of row will start from the last row.
        for (int i = order - 1; i > 0; --i)
        {
            if (matrix[i][0] > matrix[i - 1][0])
            {
                swap(matrix[i], matrix[i - 1]);
                swap(identity[i], identity[i - 1]);
            }
        }

        // Replace a row by sum of itself and a
        // constant multiple of another row of the matrix.
        for (int i = 0; i < order; ++i)
        {
            for (int j = 0; j < order; ++j)
            {
                if (j != i)
                {
                    Complex<T> temp = matrix[j][i] / matrix[i][i];
                    for (int k = 0; k < order; ++k)
                    {
                        matrix[j][k] -= matrix[i][k] * temp;
                        identity[j][k] = identity[i][k] * temp;
                    }
                }
            }
        }

        // Multiply each row by a nonzero integer.
        // Divide row element by the diagonal element
        for (int i = 0; i < order; ++i)
        {
            Complex<T> temp = matrix[i][i];
            for (int j = 0; j < order; ++j)
            {
                matrix[i][j] /= temp;
                identity[i][j] /= temp;
            }
        }

        return identity;
    }

    // Function to print out the matrix
    void print()
    {
        cout << endl;
        for (int i = 0; i < order; ++i)
        {
            for (int j = 0; j < order; ++j)
            {
                this->matrix[i][j].print();
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
    }

    ComplexMatrix() {

    }
};



#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H