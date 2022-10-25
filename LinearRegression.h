#ifndef ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H
#define ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H

#include "ComplexMatrix.h"

struct LinearRegression {
    vector<Complex<float>> coefficients;
    Complex<float> meanSquaredError;
};

LinearRegression buildLinearRegression(ComplexMatrix<float> Y, ComplexMatrix<float> X) {
    if (Y.m != 1 || Y.n != X.n) {
        printError(6);
        return {};
    }

    ComplexMatrix<float> NewX(X.n, X.m + 1);    
    ComplexMatrix<float> CoefficientsMatrix;
    vector<Complex<float>> coefficientsVector;
    LinearRegression linearRegression;
    Complex<float> mse(0, 0);   

    for (int i = 0; i < X.n; i++) {
        NewX[i][0] = Complex<float>(1, 0);

        for (int j = 1; j <= X.m; j++) {
            NewX[i][j] = X[i][j - 1];
        }
    }
    

    CoefficientsMatrix = (NewX.getTranspose() * NewX).getInverseGaussJordan() * NewX.getTranspose() * Y;
    
    for (int i = 0; i < CoefficientsMatrix.n; i++) {
        coefficientsVector.push_back(CoefficientsMatrix[i][0]);
    }

    for (int i = 0; i < Y.n; i++) {
        Complex<float> yReg(0, 0);

        for (int j = 0; j < NewX[0].size(); j++) {
            yReg += NewX[i][j] * coefficientsVector[j];
        }

        mse += (Y[i][0] - yReg) * (Y[i][0] - yReg);
    }

    mse /= Complex<float>(Y.n, 0);

    linearRegression.coefficients = coefficientsVector;
    linearRegression.meanSquaredError = mse;

    return linearRegression;
}

#endif //ALGORITHMSGROUPPROJECT_LINEARREGRESSION_H