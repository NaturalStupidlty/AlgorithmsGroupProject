#include "Headers/ComplexMatrix.h"
#include "Headers/Doctest/doctest.h"

template <typename T> void testMultiplicationErrorDifference(int order, T epsilon) {
    ComplexMatrix<T> Matrix1 = ComplexMatrix<T>::getRandom(order);
    ComplexMatrix<T> Matrix2 = ComplexMatrix<T>::getRandom(order);
    ComplexMatrix<T> Strassen = Matrix1.StrassenMultiply(Matrix2);
    ComplexMatrix<T> Regular = Matrix1 * Matrix2;
    bool valid = true;
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            if ((Strassen[i][j] - Regular[i][j]).abs() > epsilon) {
                valid = false;
                break;
            }
        }
    }
    CHECK(valid);
}

TEST_CASE("Test getInverseGaussJordan Errors") {
    ComplexMatrix<double> Matrix1(10,9);
    ComplexMatrix<double> Matrix2(10 ,9);
    CHECK(Matrix1 == (Matrix1.StrassenMultiply(Matrix2)));
}

TEST_CASE("Test StrassenAlgorithm Work") {
    SUBCASE("float test") {
        SUBCASE("10x10 test") {
            testMultiplicationErrorDifference(10, (float)1e14);
        }
        SUBCASE("100x100 test") {
            testMultiplicationErrorDifference(100, (float)1e16);
        }
    }

    SUBCASE("double test") {
        SUBCASE("10x10 test") {
            testMultiplicationErrorDifference(10, (double)1e5);
        }
        SUBCASE("100x100 test") {
            testMultiplicationErrorDifference(100, (double)1e7);
        }
    }
}
