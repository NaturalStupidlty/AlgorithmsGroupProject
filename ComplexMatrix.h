#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include "Complex.h"
#include <vector>

using std::cout;
using std::swap;
using std::vector;

template <typename T> class ComplexMatrix
{
private:
    int order {};
    vector<vector<Complex<T>>> matrix;

    Complex<T> compute_z(int col, int row, ComplexMatrix<T> lower, ComplexMatrix<T> Z, ComplexMatrix<T> I) {
        Complex<T> sum = Complex<T>(0);
        for(int i = 0; i < this->order; i++) {
            if(i != row) {
                sum += lower[row][i] * Z[i][col];
            }
        }

        Complex<T> result = I[row][col] - sum;
        result = result / lower[row][row];

        return result;
    }

    Complex<T> compute_inverse(int col, int row, ComplexMatrix<T> upper, ComplexMatrix<T> Z, ComplexMatrix<T> inverse) {
        Complex<T> sum = Complex<T>(0);
        for(int i = 0; i < this->order; i++) {
            if(i != row) {
                sum += upper[row][i] * inverse[i][col];
            }
        }

        Complex<T> result = Z[row][col] - sum;
        result = result / upper[row][row];


        return result;
    }

    ComplexMatrix<T> inverse_matrix(ComplexMatrix<T> mat, ComplexMatrix<T> lower, ComplexMatrix<T> upper, ComplexMatrix<T> Z, ComplexMatrix<T> I, ComplexMatrix<T> inverse) {
        int i, j, k;
        for (i = 0; i < this->order; i++) {
            for (j = 0; j < this->order; j++) {
                if (j < i) {
                    lower[j][i] = Complex<T>(0);
                }
                else {
                    lower[j][i] = mat[j][i];
                    for (k = 0; k < i; k++) {
                        lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
                    }
                }
            }
            for (j = 0; j < this->order; j++) {
                if (j < i) {
                    upper[i][j] = Complex<T>(0);
                }
                else if (j == i) {
                     upper[i][j] = Complex<T>(1);
                }
                else {
                    upper[i][j] = mat[i][j] / lower[i][i];
                    for (k = 0; k < i; k++) {
                        upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
                    }
                }
            }
        }

        // compute z
        for(int col = 0; col < this->order; col++) {
            for(int row = 0; row < this->order; row++) {
                Z[row][col] = compute_z(col, row, lower, Z, I);
            }
        }

        // compute inverse
        for(int col = 0; col < this->order; col++) {
            for(int row = this->order - 1; row >= 0; row--) {
                inverse[row][col] = compute_inverse(col, row, upper, Z, inverse);
            }
        }

        upper.print();
        lower.print();

        return inverse;
    }
public:
    // Дефолтний конструктор
    ComplexMatrix() = default;

    // Конструктор копій
    ComplexMatrix (const ComplexMatrix &value) {
        this->order = value.order;
        this->matrix = value.matrix;
    }

    // Створити матрицю NxN з нулів
    explicit ComplexMatrix(int N) {
        this->order = N;
        for (int i = 0; i < this->order; ++i) {
            vector<Complex<T>> line;
            for (int j = 0; j < this->order; ++j) {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    // Перевантаження []
    vector<Complex<T>>& operator [] (const int& i) {
        return this->matrix[i];
    }

    // Створити одиничну матрицю
    static ComplexMatrix<T> getIdentity(int N) {
        ComplexMatrix<T> identity(N);
        for (int i = 0; i < N; ++i) {
            identity[i][i].setReal(1);
        }
        return identity;
    }

    // Створити матрицю з рандомними значеннями
    static ComplexMatrix<T> getRandom(int order) {
        ComplexMatrix<T> F(order);
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < order; ++j) {
                F[i][j] = Complex<T>(rand() % 10000, rand()% 10000);
            }
        }
        return F;
    }

    // Функція для пошуку оберненої матриці методом Жордана Гауса
    ComplexMatrix<T> getInverseGaussJordan() {
        // Одинична матриця
        /* 1 0 0
           0 1 0
           0 0 1 */
        ComplexMatrix<T> identity = ComplexMatrix<T>::getIdentity(this->order);
        // Копія, щоб не змінювати реальну
        ComplexMatrix<T> matrixCopy = ComplexMatrix(*this);

        for (int i = 0; i < this->order; i++) {
            // Діагоналі елементи перетворюємо в 1
            /* (a+b*i) * ((a-b*i) / (a^2 + b^2)) = 1 */
            Complex<T> mul = Complex<T>(matrixCopy[i][i].getReal(), - matrixCopy[i][i].getImaginary())
                    / ((matrixCopy[i][i].getReal() * matrixCopy[i][i].getReal())
                    + (matrixCopy[i][i].getImaginary() * matrixCopy[i][i].getImaginary()));

            for (int j = 0; j < this->order; j++) {
                identity[i][j] *= mul;
            }
            for (int j = i; j < this->order; j++) {
                matrixCopy[i][j] *= mul;
            }

            // Елементи під діагоналлю в 0
            for (int k = i + 1 ; k < this->order; k++) {
                T realPart = matrixCopy[k][i].getReal();
                T imaginaryPart = matrixCopy[k][i].getImaginary();
                for (int j = 0; j < this->order; j++) {
                    matrixCopy[k][j] -= (matrixCopy[i][j] * Complex<T>(realPart, imaginaryPart));

                    identity[k][j] -= (identity[i][j]  * Complex<T>(realPart, imaginaryPart));
                }
            }

            // елементи над діагоналлю в 0
            for (int k = i - 1 ; k >= 0 ; k--) {
                T realPart = matrixCopy[k][i].getReal();
                T imaginaryPart = matrixCopy[k][i].getImaginary();
                for (int j = 0; j < this->order; j++) {
                    matrixCopy[k][j] -= (matrixCopy[i][j] * Complex<T>(realPart, imaginaryPart));

                    identity[k][j] -= (identity[i][j] * Complex<T>(realPart, imaginaryPart));
                }
            }
        }
        return identity;
    }

    // Функція для пошуку оберненої матриці методом LU-розкладу
    ComplexMatrix<T> getInverseLU() {

        ComplexMatrix<T> mat = ComplexMatrix(*this);
        ComplexMatrix<T> I = ComplexMatrix<T>::getIdentity(this->order);
        ComplexMatrix<T> Z(this->order);
        ComplexMatrix<T> inverse(this->order), lower(this->order), upper(this->order);

        mat.print();

        return inverse_matrix(mat, lower, upper, Z, I, inverse);
    }

    // Видрукувати матрицю
    void print() {
        cout << endl;
        for (int i = 0; i < this->order; ++i) {
            for (int j = 0; j < this->order; ++j) {
                this->matrix[i][j].print();
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
    }
};
#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
