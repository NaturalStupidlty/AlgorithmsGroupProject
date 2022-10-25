#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include "Complex.h"
#include "Errors.h"
#include <algorithm>
#include <cmath>
#include <vector>

using std::cout;
using std::swap;
using std::vector;
using std::max;

template <typename T> class ComplexMatrix
{
private:
    int n {};
    int m {};
    vector<vector<Complex<T>>> matrix;

    // stackoverflow ?
    void STRASSEN_algorithmA(ComplexMatrix<T> A, ComplexMatrix<T> B, ComplexMatrix<T>& C)
    {
        // base case
        if (A.n == 1)
        {
            C[0][0] = A[0][0] * B[0][0];
            return;
        }
        int newSize = A.n / 2;
        ComplexMatrix<T>
                a11(newSize), a12(newSize), a21(newSize), a22(newSize),
                b11(newSize), b12(newSize), b21(newSize), b22(newSize),
                c11(newSize), c12(newSize), c21(newSize), c22(newSize),
                p1(newSize), p2(newSize), p3(newSize), p4(newSize),
                p5(newSize), p6(newSize), p7(newSize),
                aResult(newSize), bResult(newSize);

        //dividing the matrices into sub-matrices:
        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + newSize];
                a21[i][j] = A[i + newSize][j];
                a22[i][j] = A[i + newSize][j + newSize];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + newSize];
                b21[i][j] = B[i + newSize][j];
                b22[i][j] = B[i + newSize][j + newSize];
            }
        }

        // Calculating p1 to p7:
        // p1 = (a11+a22) * (b11+b22)
        STRASSEN_algorithmA((a11 + a22), (b11 + b22), p1);

        // p2 = (a21+a22) * (b11)
        STRASSEN_algorithmA(a21 + a22, b11, p2);

        // p3 = (a11) * (b12 - b22)
        STRASSEN_algorithmA(a11, b12 - b22, p3);

        // p4 = (a22) * (b21 - b11)
        STRASSEN_algorithmA(a22, b21 - b11, p4);

        // p5 = (a11+a12) * (b22)
        STRASSEN_algorithmA(a11 + a12, b22, p5);

        // p6 = (a21-a11) * (b11+b12)
        STRASSEN_algorithmA(a21 - a11, b11 + b12, p6);

        // p7 = (a12-a22) * (b21+b22)
        STRASSEN_algorithmA(a12 - a22, b21 + b22, p7);

        // calculating c21, c21, c11, c22:

        c12 = p3 + p5;
        c21 = p2 + p4;

        c11 = ((p1 + p4) + p7) - p5;

        c22 = ((p1 + p3) + p6) - p2;

        // Grouping the results obtained in a single matrix:
        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                C[i][j] = c11[i][j];
                C[i][j + newSize] = c12[i][j];
                C[i + newSize][j] = c21[i][j];
                C[i + newSize][j + newSize] = c22[i][j];
            }
        }
    }

    inline static int nextPowerOf2(int k)
    {
        return (int)pow(2, ceil(log2(k)));
    }

    void swapRows(const int& firstRow, const int& secondRow) {
        for (int i = 0; i < this->n; i++) {
            Complex<T> t = this->matrix[firstRow][i];
            this->matrix[firstRow][i] = this->matrix[secondRow][i];
            this->matrix[secondRow][i] = t;
        }
    }
public:
    // Дефолтний конструктор
    ComplexMatrix() = default;

    // Конструктор копій
    ComplexMatrix (const ComplexMatrix& complexMatrix) {
        this->n = complexMatrix.n;
        this->m = complexMatrix.m;
        this->matrix = complexMatrix.matrix;
    }

    // Створити матрицю NxM з нулів
    ComplexMatrix(const int& N, const int& M) {
        this->n = N;
        this->m = M;
        for (int i = 0; i < this->n; ++i) {
            vector<Complex<T>> line;
            for (int j = 0; j < this->m; ++j) {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    // Створити матрицю NxN з нулів
    explicit ComplexMatrix(const int& N) {
        (*this) = ComplexMatrix<T>(N, N);
    }

    // Перевантаження []
    inline vector<Complex<T>>& operator [] (const int& i) {
        return this->matrix[i];
    }

    // Перевантаження +
    ComplexMatrix<T> operator + (ComplexMatrix<T> complexMatrix) {
        if (this->n != complexMatrix.n || this->m != complexMatrix.m)
        {
            printError(3);
            return *this;
        }
        ComplexMatrix<T> Result(this->n, this->m);
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                Result[i][j] = (*this)[i][j] + complexMatrix[i][j];
            }
        }
        return Result;
    }

    // Перевантаження -
    ComplexMatrix<T> operator - (ComplexMatrix<T> complexMatrix) {
        if (this->n != complexMatrix.n || this->m != complexMatrix.m)
        {
            printError(3);
            return *this;
        }
        ComplexMatrix<T> Result(this->n, this->m);
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                Result[i][j] = (*this)[i][j] - complexMatrix[i][j];
            }
        }
        return Result;
    }

    // Перевантаження *
    // Функція для множення матриць методом Штрассена
    ComplexMatrix<T> operator * (ComplexMatrix<T> complexMatrix)
    {

        if (this->m != complexMatrix.n)
        {
            printError(5);
            return *this;
        }
        int size = nextPowerOf2(max({ this->n, this->m, complexMatrix.m}));
        ComplexMatrix<T> AResized(size), BResized(size), Product(size);

        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                AResized[i][j] = (*this)[i][j];
            }
        }
        for (int i = 0; i < complexMatrix.n; i++)
        {
            for (int j = 0; j < complexMatrix.m; j++)
            {
                BResized[i][j] = complexMatrix[i][j];
            }
        }

        STRASSEN_algorithmA(AResized, BResized, Product);

        ComplexMatrix Result(this->n, complexMatrix.m);
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < complexMatrix.m; j++)
            {
                Result[i][j] = Product[i][j];
            }
        }
        return Result;
    }

    // Створити одиничну матрицю
    static ComplexMatrix<T> getIdentity(const int& N) {
        ComplexMatrix<T> identity(N);
        for (int i = 0; i < N; i++) {
            identity[i][i].setReal(1);
        }
        return identity;
    }

    // Створити матрицю з рандомними значеннями
    static ComplexMatrix<T> getRandom(const int& N, const int& M) {
        ComplexMatrix<T> F(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                F[i][j] = Complex<T>(rand() % 100000, rand()% 100000);
            }
        }
        return F;
    }

    // Функція для пошуку оберненої матриці методом Жордана Гауса О(n^3)
    ComplexMatrix<T> getInverseGaussJordan() {
        if (this->m != this->n) {
            printError(4);
            return *this;
        }

        // CHECK DETERMINANT !!!

        // Одинична матриця
        ComplexMatrix<T> identity = ComplexMatrix<T>::getIdentity(this->n);
        // Копія, щоб не змінювати реальну
        ComplexMatrix<T> matrixCopy = ComplexMatrix(*this);
        
        for (int i = 0; i < this->n; i++) {
            // Якщо 0, то шукаємо перший ненульовий і свапаємо
            if (matrixCopy[i][i] == 0) {
                int t = i + 1;
                while (matrixCopy[t][i] == 0) {
                    t++;
                }
                matrixCopy.swapRows(i, t);
                identity.swapRows(i, t);
            }

            // Ділимо на a + bi
            Complex<T> divider = matrixCopy[i][i];

            for (int j = 0; j < this->n; j++) {
                identity[i][j] /= divider;
            }
            for (int j = i + 1; j < this->n; j++) {
                matrixCopy[i][j] /= divider;
            }

            // Елементи під діагоналлю в 0
            for (int k = i + 1; k < this->n; k++) {
                Complex<T> factor = matrixCopy[k][i];

                for (int j = 0; j < this->n; j++) {
                    if (j >= i) matrixCopy[k][j] -= (matrixCopy[i][j] * factor);
                    identity[k][j] -= (identity[i][j] * factor);
                }                
            }

            // елементи над діагоналлю в 0
            for (int k = i - 1; k >= 0; k--) {
                Complex<T> factor = matrixCopy[k][i];

                for (int j = 0; j < this->n; j++) {
                    if (j >= i) matrixCopy[k][j] -= (matrixCopy[i][j] * factor);
                    identity[k][j] -= (identity[i][j] * factor);
                }
            }
        }
        return identity;
    }

    // Функція для пошуку оберненої матриці методом LU-розкладу
    ComplexMatrix<T> getInverseLU()
    {
        if (this->m != this->n) {
            printError(4);
            return *this;
        }
        // Верхня трикутна матриця, нижня трикутна матриця
        // рахує правильно
        ComplexMatrix<T> Upper = ComplexMatrix(*this),
        Lower = ComplexMatrix::getIdentity(this->n);
        for (int i = 0; i < this->n; i++) {
            // Якщо 0, то шукаємо перший ненульовий і свапаємо
            if (Upper[i][i] == 0) {
                int t = i + 1;
                while (Upper[t][i] == 0) {
                    t++;
                }
                Upper.swapRows(i, t);
            }

            for (int k = i + 1; k < this->n; k++) {
                Complex<T> factor = Upper[k][i];
                Lower [k][i] = Upper[k][i] / Upper[i][i];
                for (int j = 0; j < this->n; j++) {
                    Complex<T> divider = Upper[i][j] / Upper[i][i];
                    if (j >= i) Upper[k][j] -= (divider * factor);
                }
            }
        }
        // можна знайти обернену матрицю для кожної з них і помножити їх
        // все працює :)
        //return ((Upper.getInverseGaussJordan() * Lower.getInverseGaussJordan()));

        // спробував через заміни, чомусь працює        
        ComplexMatrix<T> Inverse(this->n);
        vector<Complex<T>> D(this->n);

        for (int i = 0; i < this->n; i++) {            
            // forward substitution
            for (int j = 0; j < this->n; j++) {
                Complex<T> numerator = i == j ? Complex<T>(1, 0) : Complex<T>(0, 0);
                for (int k = 0; k < j; k++) {
                    numerator -= Lower[j][k] * D[k];
                }
                D[j] = numerator;
            }
            // backward substitution
            for (int j = this->n - 1; j >= 0; j--) {
                Complex<T> numerator = D[j] ;
                for (int k = j + 1; k < n; k++) {
                    numerator -= Upper[j][k] * Inverse[k][i];
                }
                Inverse[j][i] = numerator / Upper[j][j];
            }            
        }
        return Inverse;
    }

    // Видрукувати матрицю
    inline void print() {
        cout << endl;
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                this->matrix[i][j].print();
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
    }
};
#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
