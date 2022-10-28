#include "../Headers/ComplexMatrix.h"
#include "../Headers/doctest.h"

TEST_CASE("10x10 float matrix getInverseGaussJordan") {
    int order = 10;
    float epsilon = 0.00001;
    ComplexMatrix<float> Matrix = ComplexMatrix<float>::getRandom(order);
    ComplexMatrix<float> identity = Matrix * (Matrix.getInverseGaussJordan());
    identity = identity - ComplexMatrix<float>::getIdentity(order);
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE(identity[i][j] <= epsilon);
        }
    }
}

TEST_CASE("10x10 double matrix getInverseGaussJordan") {
    int order = 10;
    double epsilon = 0.0000000000001;
    ComplexMatrix<double> Matrix = ComplexMatrix<double>::getRandom(order);
    ComplexMatrix<double> identity = Matrix * (Matrix.getInverseGaussJordan());
    identity = identity - ComplexMatrix<double>::getIdentity(order);
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE(identity[i][j] <= epsilon);
        }
    }
}

TEST_CASE("100x100 float matrix getInverseGaussJordan") {
    int order = 100;
    float epsilon = 0.001;
    ComplexMatrix<float> Matrix = ComplexMatrix<float>::getRandom(order);
    ComplexMatrix<float> identity = Matrix * (Matrix.getInverseGaussJordan());
    identity = identity - ComplexMatrix<float>::getIdentity(order);
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE(identity[i][j] <= epsilon);
        }
    }
}

TEST_CASE("100x100 double matrix getInverseGaussJordan") {
    int order = 100;
    double epsilon = 0.000000000001;
    ComplexMatrix<double> Matrix = ComplexMatrix<double>::getRandom(order);
    ComplexMatrix<double> identity = Matrix * (Matrix.getInverseGaussJordan());
    identity = identity - ComplexMatrix<double>::getIdentity(order);
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE(identity[i][j] <= epsilon);
        }
    }
}
