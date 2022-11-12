#include "Headers/ComplexMatrix.h"
#include "Headers/Doctest/doctest.h"

template <typename T> void testMultiplicationErrorDifference(int order, T epsilon) {
    ComplexMatrix<T> Matrix1 = ComplexMatrix<T>::getRandom(order, order);
    ComplexMatrix<T> Matrix2 = ComplexMatrix<T>::getRandom(order, order);
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
            testMultiplicationErrorDifference(65, 0);
        }
        SUBCASE("100x100 test") {
            testMultiplicationErrorDifference(128, 0);
        }
    }

    SUBCASE("double test") {
        SUBCASE("10x10 test") {
            testMultiplicationErrorDifference(65, 0);
        }
        SUBCASE("100x100 test") {
            testMultiplicationErrorDifference(128, 0);
        }
    }
}
