#ifndef ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
#define ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H

#include "ComplexMatrix.h"

template <typename T> struct LinearRegression {
    vector<Complex<T>> coefficients;
    Complex<T> meanSquaredError;
};

template <typename T> LinearRegression<T> buildLinearRegression(ComplexMatrix<T> Y, ComplexMatrix<T> X) {
    if (Y.getColumns() != 1 || Y.getRows() != X.getRows() || X.getRows() <= X.getColumns()) {
        printError(CANNOT_BUILD_LINEAR_REGRESSION_ERROR_CODE);
        return {};
    }

    ComplexMatrix<T> NewX(X.getRows(), X.getColumns() + 1);
    ComplexMatrix<T> NewXTransposed(X.getColumns() + 1, X.getRows());
    ComplexMatrix<T> CoefficientsMatrix;
    vector<Complex<T>> coefficientsVector;
    LinearRegression<T> linearRegression;
    Complex<T> mse(0, 0);

    for (int i = 0; i < X.getRows(); i++) {
        NewX[i][0] = Complex<T>(1, 0);

        for (int j = 1; j <= X.getColumns(); j++) {
            NewX[i][j] = X[i][j - 1];
        }
    }

    NewXTransposed = NewX.getTransposed();

    CoefficientsMatrix = (NewXTransposed * NewX).getInverseGaussJordan() * NewXTransposed * Y;

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

    linearRegression.coefficients = coefficientsVector;
    linearRegression.meanSquaredError = mse;

    return linearRegression;
}

#endif //ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
