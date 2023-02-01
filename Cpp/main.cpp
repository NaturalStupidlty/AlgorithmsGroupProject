#include "Headers/Benchmarks.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "Headers/Doctest/doctest.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
/*    // Кирилиця на windows
    #ifdef _WIN32
    system("chcp 65001");
    #endif

    // Для проходження unit tests
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int result = context.run();
    if(context.shouldExit())
    {
        return result;
    }
    // Бенчмарки
    cout << "~~~~~~~~~~~~~~~~ Benchmarks ~~~~~~~~~~~~~~~~" << endl;
    timeTestInverseGaussJordan(128, 10);
    timeTestInverseLU(100, 10);
    timeTestStrassenAlgorithm(100, 100, 10);
    timeTestRegularMultiplication(100, 100, 10);
    timeLinearRegression(5, 10, 10);*/

    ComplexMatrix<double> m(3);
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0.5;

    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;

    m[2][0] = 1;
    m[2][1] = 0;
    m[2][2] = 1;

    m.getInverseMinors().print();
    m.getInverseLU().print();
    return 0;
}