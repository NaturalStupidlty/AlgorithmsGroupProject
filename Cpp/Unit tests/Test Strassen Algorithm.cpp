#include "Headers/ComplexMatrix.h"
#include "Headers/Doctest/doctest.h"

template <typename T> void testMultiplicationErrorDifference(int order, T epsilon) {
    ComplexMatrix<T> Matrix1 = ComplexMatrix<T>::getRandom(order, order, (T)100000);
    ComplexMatrix<T> Matrix2 = ComplexMatrix<T>::getRandom(order, order, (T)100000);
    ComplexMatrix<T> Strassen = Matrix1.StrassenMultiply(Matrix2);
    ComplexMatrix<T> Regular = Matrix1 * Matrix2;
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            REQUIRE((Strassen[i][j] - Regular[i][j]).abs() <= epsilon);
        }
    }
}

TEST_CASE("Test getInverseGaussJordan Errors") {
    ComplexMatrix<double> Matrix1(10,9);
    ComplexMatrix<double> Matrix2(10 ,9);
    CHECK(Matrix1 == (Matrix1.StrassenMultiply(Matrix2)));
}

TEST_CASE("Test StrassenAlgorithm Work") {
    SUBCASE("float test") {
        SUBCASE("10x10 test") {
            // 1000 range - 10
            // 10000 range - 1e3
            // 100000 range - 1e5
            // INT_MAX range - 1e14
            testMultiplicationErrorDifference(65, (float)1e14);
        }
        SUBCASE("100x100 test") {
            // 1000 range - 10
            // 10000 range - 1e3
            // 100000 range - 1e5
            // INT_MAX range - 1e14
            testMultiplicationErrorDifference(128, (float)1e16);
        }
    }

    SUBCASE("double test") {
        SUBCASE("10x10 test") {
            // 1000 range - 1e-8
            // 10000 range - 1e-6
            // 100000 range - 1e-3
            // INT_MAX range - 1e5
            testMultiplicationErrorDifference(65, (double)1e5);
        }
        SUBCASE("100x100 test") {
            // 1000 range - 1e-6
            // 10000 range - 1e-4
            // 100000 range - 1e-1
            // INT_MAX range - 1e7
            testMultiplicationErrorDifference(128, (double)1e7);
        }
    }
}
