#ifndef ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H
#define ALGORITHMSGROUPPROJECT_COMPLEXMATRIX_H

#include "Complex.h"
#include <vector>

using std::cout;
using std::vector;
using std::max;

/** Complex Matrix class
 *
 * @tparam T type
 */
template <typename T> class ComplexMatrix
{
private:
    unsigned int rows {};
    unsigned int columns {};
    vector<vector<Complex<T>>> matrix;

    /** Swaps two rows of a matrix
     *
     * @param firstRow
     * @param secondRow
     */
    void swapRows(const int& firstRow, const int& secondRow) {
        for (int i = 0; i < this->columns; i++) {
            Complex<T> rowCopy = this->matrix[firstRow][i];
            this->matrix[firstRow][i] = this->matrix[secondRow][i];
            this->matrix[secondRow][i] = rowCopy;
        }
    }

    /** Swaps two columns of a matrix
     *
     * @param firstColumn
     * @param secondColumn
     */
    void swapColumns(const int& firstColumn, const int& secondColumn) {
        for (int i = 0; i < this->rows; i++) {
            Complex<T> columnCopy = this->matrix[i][firstColumn];
            this->matrix[i][firstColumn] = this->matrix[i][secondColumn];
            this->matrix[i][secondColumn] = columnCopy;
        }
    }

    /** Find LU decomposition of a matrix
     *
     * @param Decomposition - matrix that will contain the decomposition
     * @param Permutations - matrix that will contain the permutations
     * @return True if there exists a decomposition and false if not
     */
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

    /** Multiply two matrices using Strassen algorithm
     *
     * @param A - left matrix
     * @param B - right matrix
     * @param Product - matrix that will contain their product
     */
    void StrassenMultiplication(ComplexMatrix<T> A, ComplexMatrix<T> B, ComplexMatrix<T>& Product) {
        // База
        if (A.rows <= 64 || A.columns || B.columns) {
            Product = A * B;
            return;
        }
        int newSize = A.rows / 2;
        ComplexMatrix<T>
                a11(newSize), a12(newSize), a21(newSize), a22(newSize),
                b11(newSize), b12(newSize), b21(newSize), b22(newSize),
                c11(newSize), c12(newSize), c21(newSize), c22(newSize),
                p1(newSize), p2(newSize), p3(newSize), p4(newSize),
                p5(newSize), p6(newSize), p7(newSize);

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

        StrassenMultiplication(a11, b12 - b22, p1);
        StrassenMultiplication(a11 + a12, b22, p2);
        StrassenMultiplication(a21 + a22, b11, p3);
        StrassenMultiplication(a22, b21 - b11, p4);
        StrassenMultiplication(a11 + a22, b11 + b22, p5);
        StrassenMultiplication(a12 - a22, b21 + b22, p6);
        StrassenMultiplication(a11 - a21, b11 + b12, p7);

        c11 = p4 + p5 + p6 - p2;
        c12 = p1 + p2;
        c21 = p3 + p4;
        c22 = p1 + p5 - p3 - p7;

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
    /** Default constructor
     *
     */
    ComplexMatrix() = default;

    /** Copy constructor
     *
     * @param Matrix - matrix to be copied
     */
    ComplexMatrix (const ComplexMatrix& Matrix) {
        this->rows = Matrix.rows;
        this->columns = Matrix.columns;
        this->matrix = Matrix.matrix;
    }

    /** Create N by M matrix with zeroes
     * O(n*m)
     *
     * @param N - rows
     * @param M - columns
     */
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

    /** Create N by N matrix with zeroes
     * O(n^2)
     *
     * @param N - rows, columns
     */
    explicit ComplexMatrix(const int& N) {
        (*this) = ComplexMatrix<T>(N, N);
    }

    /** Find number of columns
     *
     * @return number of columns
     */
    unsigned int getColumns() {
        return this->columns;
    }

    /** Find number of rows
     *
     * @return number of rows
     */
    unsigned int getRows() {
        return this->rows;
    }

    /** Create N by N identity matrix
    * O(n^2)
    *
    * @param N - rows, columns
    */
    static ComplexMatrix<T> getIdentity(const int& N) {
        ComplexMatrix<T> Identity(N);
        for (int i = 0; i < N; i++) {
            Identity[i][i].setReal(1);
        }
        return Identity;
    }

    /** Create N by M matrix with random numbers
     * O(n*m)
     *
     * @param N - rows
     * @param M - columns
     * @param range - range of random numbers (-range, range)
     */
    static ComplexMatrix<T> getRandom(const int& N, const int& M, T range = INT_MAX) {
        ComplexMatrix<T> Random(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Random[i][j] = Complex<T>::getRandomNumber(-range, range);
            }
        }
        return Random;
    }

    /** Find inverse matrix using Gauss-Gordan method
     * О(n^3)
     *
     * @return inverse matrix
     */
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

    /** Find inverse matrix using LU-decomposition method
     * О(n^3)
     *
     * @return inverse matrix
     */
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

    /** Find transposed matrix
     * O(n^2)
     *
     * @return transposed matrix
     */
    ComplexMatrix<T> getTransposed() {
        ComplexMatrix<T> Transposed(this->columns, this->rows);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                Transposed[j][i] = (*this)[i][j];
            }
        }
        return Transposed;
    }

    /** Get [i] row
     * O(1)
     *
     * @param i - row number from 0 to n
     * @return
     */
    inline vector<Complex<T>>& operator [] (const int& i) {
        return this->matrix[i];
    }

    /** Add two matrices
     * O(n*m)
     *
     * @param Matrix - right matrix
     * @return sum
     */
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

    /** Subtract two matrices
     * O(n*m)
     *
     * @param Matrix - right matrix
     * @return difference
     */
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

    /** Check if two matrices are equal
     * O(n*m)
     *
     * @param Matrix - right matrix
     * @return True if they are equal, false otherwise
     */
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

    /** Multiply two matrices
     * O(n^3)
     *
     * @param Matrix - right matrix
     * @return product
     */
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

    /** Multiply two matrices using Strassen Multiply
     * O(n^(log2(7))) ~ O(n^2.8074)
     * if n <= 64
     * O(n^3)
     *
     * @param Matrix - right matrix
     * @return product
     */
    ComplexMatrix<T> StrassenMultiply(ComplexMatrix<T> Matrix) {
        if (this->columns != Matrix.rows) {
            printError(CANNOT_MULTIPLY_ERROR_CODE);
            return *this;
        }
        // Next power of 2
        int power = max({ this->rows, this->columns, Matrix.columns});
        int size = (int)pow(2, ceil(log2(power)));
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

    /** Print matrix
     * O(n*m)
     *
     */
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
