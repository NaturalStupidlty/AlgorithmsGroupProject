#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include "Complex.h"
#include <vector>

using std::cout;
using std::vector;
using std::max;

template <typename T> class ComplexMatrix
{
private:
    unsigned int rows {};
    unsigned int columns {};
    vector<vector<Complex<T>>> matrix;

    // Наступний степінь числа 2
    inline static int nextPowerOf2(int power) {
        return (int)pow(2, ceil(log2(power)));
    }

    // Поміняти місцями 2 рядки
    void swapRows(const int& firstRow, const int& secondRow) {
        for (int i = 0; i < this->columns; i++) {
            Complex<T> rowCopy = this->matrix[firstRow][i];
            this->matrix[firstRow][i] = this->matrix[secondRow][i];
            this->matrix[secondRow][i] = rowCopy;
        }
    }

    // Поміняти місцями 2 стовпчики
    void swapColumns(const int& firstColumn, const int& secondColumn) {
        for (int i = 0; i < this->rows; i++) {
            Complex<T> columnCopy = this->matrix[i][firstColumn];
            this->matrix[i][firstColumn] = this->matrix[i][secondColumn];
            this->matrix[i][secondColumn] = columnCopy;
        }
    }

    // Повертає true, якщо можна знайти розклад і false, якщо ні
    bool getLUDecomposition(ComplexMatrix<T>& Decomposition, ComplexMatrix<T>& Permutations) {
        // Верхня, нижня трикутні матриці та матриця перестановок
        if (this->columns != this->rows) {
            printError(CANNOT_FIND_LU_DECOMPOSITION_ERROR_CODE);
            return false;
        }

        // Верхня трикутна матриця, нижня трикутні матриці
        // зберігаються в Decomposition
        // Decomposition = Lower + Upper - E
        // E - одинична матриця
        Decomposition = ComplexMatrix(*this),
                Permutations = ComplexMatrix::getIdentity(this->rows);

        for (int i = 0; i < rows; i++) {
            // Пошук опорного елемента
            int supportElement = i;
            while (supportElement < this->rows && Decomposition[supportElement][i] == 0) {
                supportElement++;
            }
            if (supportElement == this->rows) {
                printError(CANNOT_FIND_LU_DECOMPOSITION_ERROR_CODE);
                return false;
            }

            // Міняємо місцями i-ту рядок і рядок з опорним елементом
            Permutations.swapRows(supportElement, i);
            Decomposition.swapRows(supportElement, i);
            for (int j = i + 1; j < rows; j++) {
                Decomposition[j][i] /= Decomposition[i][i];
                for (int k = i + 1; k < rows; k++)
                    Decomposition[j][k] -= Decomposition[j][i] * Decomposition[i][k];
            }
        }
        return true;
    }

    // Множення матриць методом Штрассена
    void StrassenMultiplication(ComplexMatrix<T> A, ComplexMatrix<T> B, ComplexMatrix<T>& Product) {
        // База
        if (A.rows == 1) {
            Product[0][0] = A[0][0] * B[0][0];
            return;
        }
        int newSize = A.rows / 2;
        ComplexMatrix<T>
                a11(newSize), a12(newSize), a21(newSize), a22(newSize),
                b11(newSize), b12(newSize), b21(newSize), b22(newSize),
                c11(newSize), c12(newSize), c21(newSize), c22(newSize),
                p1(newSize), p2(newSize), p3(newSize), p4(newSize),
                p5(newSize), p6(newSize), p7(newSize),

                s1(newSize), s2(newSize), s3(newSize),
                s4(newSize), s5(newSize), s6(newSize),
                s7(newSize), s8(newSize), s9(newSize),
                s10(newSize);

        // Ділимо матриці на підматриці
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
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

        // p1 = (a11+a22) * (b11+b22)

        s1 = a11 + a22;
        s2 = b11 + b22;
        s3 = a21 + a22;
        s4 = b12 - b22;
        s5 = b21 - b11;
        s6 = a11 + a12;
        s7 = a21 - a11;
        s8 = b11 + b12;
        s9 = a12 - a22;
        s10 = b21 + b22;

        StrassenMultiplication(s1, s2, p1);

        // p2 = (a21+a22) * (b11)
        StrassenMultiplication(s3, b11, p2);

        // p3 = (a11) * (b12 - b22)
        StrassenMultiplication(a11, s4, p3);

        // p4 = (a22) * (b21 - b11)
        StrassenMultiplication(a22, s5, p4);

        // p5 = (a11+a12) * (b22)
        StrassenMultiplication(s6, b22, p5);

        // p6 = (a21-a11) * (b11+b12)
        StrassenMultiplication(s7, s8, p6);

        // p7 = (a12-a22) * (b21+b22)
        StrassenMultiplication(s9, s10, p7);

        //  c21, c21, c11, c22:
        c12 = p3 + p5;
        c21 = p2 + p4;
        c11 = ((p1 + p4) + p7) - p5;
        c22 = ((p1 + p3) + p6) - p2;

        // Складаємо результат у єдину матрицю:
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                Product[i][j] = c11[i][j];
                Product[i][j + newSize] = c12[i][j];
                Product[i + newSize][j] = c21[i][j];
                Product[i + newSize][j + newSize] = c22[i][j];
            }
        }
    }
public:
    // Дефолтний конструктор
    ComplexMatrix() = default;

    // Конструктор копій
    ComplexMatrix (const ComplexMatrix& Matrix) {
        this->rows = Matrix.rows;
        this->columns = Matrix.columns;
        this->matrix = Matrix.matrix;
    }

    // Створити матрицю NxM з нулів
    // O(n^2)
    inline ComplexMatrix(const int& N, const int& M) {
        this->rows = N;
        this->columns = M;
        for (int i = 0; i < this->rows; ++i) {
            vector<Complex<T>> line;
            for (int j = 0; j < this->columns; ++j) {
                Complex<T> number;
                line.push_back(number);
            }
            matrix.push_back(line);
        }
    }

    // Створити матрицю NxN з нулів
    // O(n^2)
    explicit ComplexMatrix(const int& N) {
        (*this) = ComplexMatrix<T>(N, N);
    }

    // Гетери
    unsigned int getColumns() {
        return this->columns;
    }

    unsigned int getRows() {
        return this->rows;
    }

    // Створити одиничну матрицю
    // O(n^2)
    static ComplexMatrix<T> getIdentity(const int& N) {
        ComplexMatrix<T> Identity(N);
        for (int i = 0; i < N; i++) {
            Identity[i][i].setReal(1);
        }
        return Identity;
    }

    // Створити матрицю NxM з випадковими значеннями
    // O(n^m)
    static ComplexMatrix<T> getRandom(const int& N, const int& M, T range = INT_MAX) {
        ComplexMatrix<T> Random(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Random[i][j] = Complex<T>::getRandomNumber(-range, range);
            }
        }
        return Random;
    }

    // Створити матрицю NxN з випадковими значеннями
    // O(n^2)
    static ComplexMatrix<T> getRandom(const int& N) {
        return getRandom(N, N);
    }

    // Функція для пошуку оберненої матриці методом Жордана Гауса
    // О(n^3)
    ComplexMatrix<T> getInverseGaussJordan() {
        // Якщо матриця не квадратна
        if (this->columns != this->rows) {
            printError(MATRIX_IS_NOT_SQUARE_ERROR_CODE);
            return *this;
        }

        // Одинична матриця
        ComplexMatrix<T> Identity = ComplexMatrix<T>::getIdentity(this->rows);
        // Копія, щоб не змінювати реальну
        ComplexMatrix<T> MatrixCopy = ComplexMatrix(*this);
        
        for (int i = 0; i < this->rows; i++) {
            // Якщо 0, то шукаємо перший ненульовий і свапаємо
            if (MatrixCopy[i][i] == 0) {
                int supportElement = i + 1;
                while (supportElement < this->rows && MatrixCopy[supportElement][i] == 0) {
                    supportElement++;
                }
                if (supportElement == this->rows) {
                    printError(CANNOT_FIND_INVERSE_MATRIX_ERROR_CODE);
                    return *this;
                }
                MatrixCopy.swapRows(i, supportElement);
                Identity.swapRows(i, supportElement);
            }

            // Ділимо на a + bi
            Complex<T> divider = MatrixCopy[i][i];

            for (int j = 0; j < this->rows; j++) {
                Identity[i][j] /= divider;
            }
            for (int j = i + 1; j < this->rows; j++) {
                MatrixCopy[i][j] /= divider;
            }

            // Елементи під діагоналлю в 0
            for (int k = i + 1; k < this->rows; k++) {
                Complex<T> factor = MatrixCopy[k][i];

                for (int j = 0; j < this->rows; j++) {
                    if (j >= i) MatrixCopy[k][j] -= (MatrixCopy[i][j] * factor);
                    Identity[k][j] -= (Identity[i][j] * factor);
                }                
            }

            // Елементи над діагоналлю в 0
            for (int k = i - 1; k >= 0; k--) {
                Complex<T> factor = MatrixCopy[k][i];

                for (int j = 0; j < this->rows; j++) {
                    if (j >= i) MatrixCopy[k][j] -= (MatrixCopy[i][j] * factor);
                    Identity[k][j] -= (Identity[i][j] * factor);
                }
            }
        }
        return Identity;
    }

    // Функція для пошуку оберненої матриці методом LU-розкладу
    // O(n^3)
    ComplexMatrix<T> getInverseLU() {
        if (this->columns != this->rows) {
            printError(MATRIX_IS_NOT_SQUARE_ERROR_CODE);
            return *this;
        }
        ComplexMatrix<T> Decomposition, Permutation;
        if (getLUDecomposition(Decomposition, Permutation) == false) {
            printError(CANNOT_FIND_INVERSE_MATRIX_ERROR_CODE);
            return *this;
        }

        // Спробував через заміни, чомусь працює
        ComplexMatrix<T> Inverse(this->rows);
        vector<Complex<T>> D(this->rows);

        for (int i = 0; i < this->rows; i++) {
            // forward substitution
            for (int j = 0; j < this->rows; j++) {
                Complex<T> numerator = i == j ? Complex<T>(1, 0) : Complex<T>(0, 0);
                for (int k = 0; k < j; k++) {
                    numerator -= Decomposition[j][k] * D[k];
                }
                D[j] = numerator;
            }
            // backward substitution
            for (int j = this->rows - 1; j >= 0; j--) {
                Complex<T> numerator = D[j] ;
                for (int k = j + 1; k < this->rows; k++) {
                    numerator -= Decomposition[j][k] * Inverse[k][i];
                }
                Inverse[j][i] = numerator / Decomposition[j][j];
            }            
        }

        for (int i = this->rows - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (Permutation[i][j] != Complex<T>(1, 0)) {
                    continue;
                }
                    
                Permutation.swapRows(i, j);
                Inverse.swapColumns(i, j);
                i++;
                break;
            }
        }

        return Inverse;
    }

    // Транспонування матриці
    // O(n^2)
    ComplexMatrix<T> getTransposed() {
        ComplexMatrix<T> Transposed(this->columns, this->rows);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                Transposed[j][i] = (*this)[i][j];
            }
        }
        return Transposed;
    }

    // Перевантаження []
    // O(1)
    inline vector<Complex<T>>& operator [] (const int& i) {
        return this->matrix[i];
    }

    // Перевантаження +
    // O(n^2)
    ComplexMatrix<T> operator + (ComplexMatrix<T> Matrix) {
        if (this->rows != Matrix.rows || this->columns != Matrix.columns) {
            printError(CANNOT_ADD_OR_SUBTRACT_ERROR_CODE);
            return *this;
        }
        ComplexMatrix<T> Result(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                Result[i][j] = (*this)[i][j] + Matrix[i][j];
            }
        }
        return Result;
    }

    // Перевантаження -
    // O(n^2)
    ComplexMatrix<T> operator - (ComplexMatrix<T> Matrix) {
        if (this->rows != Matrix.rows || this->columns != Matrix.columns) {
            printError(CANNOT_ADD_OR_SUBTRACT_ERROR_CODE);
            return *this;
        }
        ComplexMatrix<T> Result(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                Result[i][j] = (*this)[i][j] - Matrix[i][j];
            }
        }
        return Result;
    }

    // Перевантаження ==
    // O(n^2)
    bool operator == (ComplexMatrix<T> Matrix) {
        if (this->rows != Matrix.rows || this->columns != Matrix.columns) {
            return false;
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if ((*this)[i][j] != Matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // Перевантаження *
    // Звичайне множення O(n^3)
    ComplexMatrix<T> operator * (ComplexMatrix<T> Matrix) {
        if (this->columns != Matrix.rows) {
            printError(CANNOT_MULTIPLY_ERROR_CODE);
            return *this;
        }
        ComplexMatrix<T> Product(this->rows, Matrix.columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < Matrix.columns; j++) {
                for (int k = 0; k < Matrix.rows; k++) {
                    Product[i][j] += (*this)[i][k] * Matrix[k][j];
                }
            }
        }
        return Product;
    }

    // Функція для множення матриць методом Штрассена
    // O(n^(log2(7))) ~ O(n^2.8074)
    ComplexMatrix<T> StrassenMultiply(ComplexMatrix<T> Matrix) {
        if (this->columns != Matrix.rows) {
            printError(CANNOT_MULTIPLY_ERROR_CODE);
            return *this;
        }
        int size = nextPowerOf2(max({ this->rows, this->columns, Matrix.columns}));
        ComplexMatrix<T> AResized(size), BResized(size), Product(size);

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                AResized[i][j] = (*this)[i][j];
            }
        }
        for (int i = 0; i < Matrix.rows; i++) {
            for (int j = 0; j < Matrix.columns; j++) {
                BResized[i][j] = Matrix[i][j];
            }
        }

        StrassenMultiplication(AResized, BResized, Product);

        ComplexMatrix Result(this->rows, Matrix.columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < Matrix.columns; j++) {
                Result[i][j] = Product[i][j];
            }
        }
        return Result;
    }

    // Видрукувати матрицю
    // O(n^2)
    inline void print() {
        cout << endl;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->matrix[i][j].print();
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
    }

};
#endif //ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
