#ifndef ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
#define ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H

#include "Headers/ComplexMatrix.h"

template <typename T> struct LinearRegression {
    vector<Complex<T>> coefficients;
    Complex<T> meanSquaredError;
};

template <typename T> LinearRegression<T> buildLinearRegression(ComplexMatrix<T> Y, ComplexMatrix<T> X) {
    if (Y.getRows() != 1 || Y.getColumns() != X.getColumns()) {
        printError(CANNOT_BUILD_LINEAR_REGRESSION_ERROR_CODE);
        return {};
    }

    ComplexMatrix<T> NewX(X.getColumns(), X.getRows() + 1);
    ComplexMatrix<T> CoefficientsMatrix;
    vector<Complex<T>> coefficientsVector;
    LinearRegression<T> linearRegression;
    Complex<T> mse(0, 0);

    for (int i = 0; i < X.getColumns(); i++) {
        NewX[i][0] = Complex<T>(1, 0);

        for (int j = 1; j <= X.getRows(); j++) {
            NewX[i][j] = X[i][j - 1];
        }
    }


    CoefficientsMatrix = (NewX.getTransposed() * NewX).getInverseGaussJordan() * NewX.getTransposed() * Y;

    for (int i = 0; i < CoefficientsMatrix.getColumns(); i++) {
        coefficientsVector.push_back(CoefficientsMatrix[i][0]);
    }

    for (int i = 0; i < Y.getColumns(); i++) {
        Complex<T> yReg(0, 0);

        for (int j = 0; j < NewX.getRows(); j++) {
            yReg += NewX[i][j] * coefficientsVector[j];
        }

        mse += (Y[i][0] - yReg) * (Y[i][0] - yReg);
    }

    mse /= Complex<T>(Y.getColumns(), 0);

    linearRegression.coefficients = coefficientsVector;
    linearRegression.meanSquaredError = mse;

    return linearRegression;
}

#endif //ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
