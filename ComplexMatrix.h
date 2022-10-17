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
    // Дефолтний конструктор
    ComplexMatrix() = default;

    // Створити матрицю NxN з нулів
    explicit ComplexMatrix(int N)
    {
        this->order = N;
        for (int i = 0; i < this->order; ++i)
        {
            vector<Complex<T>> line;
            for (int j = 0; j < this->order; ++j)
            {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    // Конструктор копій
    ComplexMatrix (const ComplexMatrix &value)
    {
        this->order = value.order;
        this->matrix = value.matrix;
    }

    // Перевантаження []
    vector<Complex<T>>& operator [] (const int& i)
    {
        return this->matrix[i];
    }

    static ComplexMatrix<T> getIdentity(int N)
    {
        ComplexMatrix<T> identity(N);
        for (int i = 0; i < N; ++i)
        {
            identity[i][i].setReal(1);
        }
        return identity;
    }

    static ComplexMatrix<T> createRandom(int order)
    {
        ComplexMatrix<T> F(order);
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < order; ++j) {
                F[i][j] = Complex<float>(rand() % 10000, rand()% 10000);
            }
        }
        return F;
    }

    // Функція для пошуку оберненої матриці методом Жордана Гауса
    ComplexMatrix<T> getInverseGaussJordan()
    {
        // Одинична матриця
        ComplexMatrix<T> identity = ComplexMatrix<T>::getIdentity(this->order);
        ComplexMatrix<T> matrixCopy = ComplexMatrix(*this);

        for (int i = 0; i < this->order; i++)
        {
            // Діагоналі елементи перетворюємо в 1

            /* 1 1 1
               1 1 1
               1 1 1 */

            /* 1 0 0
               0 1 0
               0 0 1 */

            /* (a+b*i) * (a-b*i) = a^2 + b^2
             * a^2 + b^2 / a^2 + b^2 = 1 */
            T realPart = matrixCopy[i][i].getReal();
            T imaginaryPart = matrixCopy[i][i].getImaginary();

            for (int j = i; j < this->order; j++)
            {
                matrixCopy[i][j] = matrixCopy[i][j] * Complex<T>(realPart, - imaginaryPart);
                matrixCopy[i][j] = matrixCopy[i][j] / Complex<T>(realPart * realPart, imaginaryPart * imaginaryPart);

                identity[i][j] = identity[i][j] * Complex<T>(realPart, - imaginaryPart);
                identity[i][j] = identity[i][j] / Complex<T>(realPart * realPart, imaginaryPart * imaginaryPart);
            }

            // елементи під діагоналлю в 0
            for (int k = i + 1 ; k < this->order; k++)
            {
                realPart = matrixCopy[k][i].getReal();
                imaginaryPart = matrixCopy[k][i].getImaginary();
                for (int j = 0; j < this->order; j++)
                {
                    matrixCopy[k][j] = matrixCopy[k][j] - (matrixCopy[i][j] * Complex<T>(realPart, imaginaryPart));

                    identity[k][j] = identity[k][j] - (identity[i][j]  * Complex<T>(realPart, imaginaryPart));
                }
            }

            // елементи під діагоналлю в 0
            for (int k = i - 1 ; k >= 0 ; k--)
            {
                realPart = matrixCopy[k][i].getReal();
                imaginaryPart = matrixCopy[k][i].getImaginary();
                for (int j = k; j < this->order; j++)
                {
                    matrixCopy[k][j] = matrixCopy[k][j] - (matrixCopy[i][j] * Complex<T>(realPart, imaginaryPart));

                    identity[k][j] = identity[k][j] - (identity[i][j]  * Complex<T>(realPart, imaginaryPart));
                }
            }

        }
        return identity;
    }

    // Видрукувати матрицю
    void print()
    {
        cout << endl;
        for (int i = 0; i < this->order; ++i)
        {
            for (int j = 0; j < this->order; ++j)
            {
                this->matrix[i][j].print();
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
    }
};
#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
