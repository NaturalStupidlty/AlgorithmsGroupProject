#ifndef ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
#define ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H

#include <stdexcept>
#include "ComplexMatrix.h"

/** Linear Regression class
 *
 * @tparam T - type
 */
template <typename T> class LinearRegression {
private:
    vector<Complex<T>> coefficients;
    Complex<T> meanSquaredError;

public:
    /** Run linear regression algorithm
     *
     * @tparam T - type
     * @param Y - matrix of target values
     * @param X - matrix of features
     */
    LinearRegression(ComplexMatrix<T> Y, ComplexMatrix<T> X) {
        if (Y.getColumns() != 1 || Y.getRows() != X.getRows() || X.getRows() <= X.getColumns()) {
            printError(CANNOT_BUILD_LINEAR_REGRESSION_ERROR_CODE);
            throw (*this);
        }

        ComplexMatrix<T> NewX(X.getRows(), X.getColumns() + 1);
        ComplexMatrix<T> NewXTransposed(X.getColumns() + 1, X.getRows());
        ComplexMatrix<T> CoefficientsMatrix;
        vector<Complex<T>> coefficientsVector;
        Complex<T> mse(0, 0);

        for (int i = 0; i < X.getRows(); i++) {
            NewX[i][0] = Complex<T>(1, 0);

            for (int j = 1; j <= X.getColumns(); j++) {
                NewX[i][j] = X[i][j - 1];
            }
        }

        NewXTransposed = NewX.getTransposed();

        CoefficientsMatrix = (NewXTransposed * NewX).getInverse("Gauss-Jordan") * NewXTransposed * Y;

        for (int i = 0; i < CoefficientsMatrix.getRows(); i++) {
            coefficientsVector.push_back(CoefficientsMatrix[i][0]);
        }

        for (int i = 0; i < Y.getRows(); i++) {
            Complex<T> yReg(0, 0);

            for (int j = 0; j < NewX.getColumns(); j++) {
                yReg += NewX[i][j] * coefficientsVector[j];
            }

            mse += (Y[i][0] - yReg) * (Y[i][0] - yReg);
        }

        mse /= Complex<T>(Y.getRows(), 0);

        this->coefficients = coefficientsVector;
        this->meanSquaredError = mse;
    }

    vector<Complex<T>> getCoefficients() {
        return this->coefficients;
    }

    Complex<T> getMeanSquaredError() {
        return this->meanSquaredError;
    }
};

#endif //ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
