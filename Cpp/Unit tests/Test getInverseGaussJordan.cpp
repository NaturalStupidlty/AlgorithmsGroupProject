#include "Headers/ComplexMatrix.h"
#include "Headers/Doctest/doctest.h"

template <typename T> void testInverseErrorDifference(int order, T epsilon) {
    ComplexMatrix<T> Matrix = ComplexMatrix<T>::getRandom(order, order);
    ComplexMatrix<T> Identity = Matrix * (Matrix.getInverse("Gauss-Jordan"));
    Identity = Identity - ComplexMatrix<T>::getIdentity(order);
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE((Identity[i][j]).abs() <= epsilon);
        }
    }
}

TEST_CASE("Test getInverseGaussJordan Errors") {
    SUBCASE("Matrix is NOT square") {
        ComplexMatrix<double> Matrix(10,9);
        CHECK(Matrix == Matrix.getInverse("Gauss-Jordan"));
    }

    SUBCASE("Matrix has a zero row") {
        ComplexMatrix<double> Matrix = ComplexMatrix<double>::getRandom(10, 10);
        for (int i = 0; i < 10; i++)
        {
            Matrix[7][i] = 0;
        }
        CHECK(Matrix == Matrix.getInverse("Gauss-Jordan"));
    }

    SUBCASE("Matrix has a zero column") {
        ComplexMatrix<double> Matrix = ComplexMatrix<double>::getRandom(10, 10);
        for (int i = 0; i < 10; i++)
        {
            Matrix[i][8] = 0;
        }
        CHECK(Matrix == Matrix.getInverse("Gauss-Jordan"));
    }

    SUBCASE("Matrix determinant is zero") {
        ComplexMatrix<double> Matrix(3);
        Matrix[0][0] = 1;
        Matrix[0][1] = 2;
        Matrix[0][2] = 3;

        Matrix[1][0] = 4;
        Matrix[1][1] = 5;
        Matrix[1][2] = 6;

        Matrix[2][0] = 7;
        Matrix[2][1] = 8;
        Matrix[2][2] = 9;

        CHECK(Matrix == Matrix.getInverse("Gauss-Jordan"));
    }
    SUBCASE("Matrix determinant is zero") {
        ComplexMatrix<double> Matrix(2);
        Matrix[0][0] = 1;
        Matrix[0][1] = Complex<double>(0, 1);

        Matrix[1][0] = Complex<double>(0, 1);
        Matrix[1][1] = -1;

        CHECK(Matrix == Matrix.getInverse("Gauss-Jordan"));
    }
}

TEST_CASE("Test getInverseGaussJordan Work") {
    SUBCASE("float test") {
        SUBCASE("10x10 test") {
            testInverseErrorDifference(10, (float)1e-4);
        }
        SUBCASE("100x100 test") {
            testInverseErrorDifference(100, (float)1e-2);
        }
    }

    SUBCASE("double test") {
        SUBCASE("10x10 test") {
            testInverseErrorDifference(10, (double)1e-13);
        }
        SUBCASE("100x100 test") {
            testInverseErrorDifference(100, (double)1e-11);
        }
    }
}
