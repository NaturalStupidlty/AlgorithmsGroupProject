#include "../Headers/doctest.h"
#include "../Headers/LinearRegression.h"

Complex<double> testAndGetErrorDifference(int varsAmount, int dataAmount, Complex<double> maxDeviation) {
    ComplexMatrix<double> Y = ComplexMatrix<double>(dataAmount, 1);
    ComplexMatrix<double> X = ComplexMatrix<double>(dataAmount, varsAmount);
    vector<Complex<double>> randCoefficients;
    Complex<double> maxMSE(0, 0);

    for (int i = 0; i <= varsAmount; i++) {
        randCoefficients.push_back(Complex<double>(rand() % 1000 - 500, 0));
    }

    for (int i = 0; i < dataAmount; i++) {
        Complex<double> yReg = randCoefficients[0];

        for (int j = 0; j < varsAmount; j++) {
            Complex<double> randX(rand() % 1000 - 500, 0);
            X[i][j] = randX;
            yReg += randCoefficients[j + 1] * randX;
        }

        Complex<double> deviation = Complex<double>((double)rand() / RAND_MAX, 0) * maxDeviation;
        maxMSE += deviation * deviation;
        Y[i][0] = yReg + deviation;
    }

    LinearRegression<double> lr = buildLinearRegression(Y, X);

    return lr.meanSquaredError - maxMSE;
}

TEST_CASE("Test Linear Regression Errors") {
    SUBCASE("Y has more than one column") {
        ComplexMatrix<double> Y = ComplexMatrix<double>(2, 2);
        ComplexMatrix<double> X = ComplexMatrix<double>(2, 1);
        CHECK(buildLinearRegression(Y, X).coefficients.size() == 0);
    }
    SUBCASE("Y and X has different amount of rows") {
        ComplexMatrix<double> Y = ComplexMatrix<double>(4, 1);
        ComplexMatrix<double> X = ComplexMatrix<double>(5, 2);
        CHECK(buildLinearRegression(Y, X).coefficients.size() == 0);
    }
    SUBCASE("X has less or equal rows than columns (not enough data for building linear regression)") {
        ComplexMatrix<double> Y = ComplexMatrix<double>(4, 1);
        ComplexMatrix<double> X = ComplexMatrix<double>(4, 4);
        CHECK(buildLinearRegression(Y, X).coefficients.size() == 0);
    }
}

TEST_CASE("Test Linear Regression Work") {
    SUBCASE("Small amount of data and small deviation") {
        CHECK((testAndGetErrorDifference(1, 5, Complex<double>(0.5, 0)) <= 0) == true);
    }
    SUBCASE("Small amount of data and medium deviation") {
        CHECK((testAndGetErrorDifference(1, 5, Complex<double>(10, 0)) <= 0) == true);
    }
    SUBCASE("Small amount of data and big deviation") {
        CHECK((testAndGetErrorDifference(1, 5, Complex<double>(100, 0)) <= 0) == true);
    }

    SUBCASE("Medium amount of data and small deviation") {
        CHECK((testAndGetErrorDifference(5, 10, Complex<double>(0.5, 0)) <= 0) == true);
    }
    SUBCASE("Medium amount of data and medium deviation") {
        CHECK((testAndGetErrorDifference(5, 10, Complex<double>(10, 0)) <= 0) == true);
    }
    SUBCASE("Medium amount of data and big deviation") {
        CHECK((testAndGetErrorDifference(5, 10, Complex<double>(100, 0)) <= 0) == true);
    }

    SUBCASE("Big amount of data and small deviation") {
        CHECK((testAndGetErrorDifference(10, 20, Complex<double>(0.5, 0)) <= 0) == true);
    }
    SUBCASE("Big amount of data and medium deviation") {
        CHECK((testAndGetErrorDifference(10, 20, Complex<double>(10, 0)) <= 0) == true);
    }
    SUBCASE("Big amount of data and big deviation") {
        CHECK((testAndGetErrorDifference(10, 20, Complex<double>(100, 0)) <= 0) == true);
    }
}