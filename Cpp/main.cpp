#include "Headers/Benchmarks.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "Headers/Doctest/doctest.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    // Кирилиця на windows
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
/*

    timeTestInverseGaussJordan(100, 10);
    timeTestInverseLU(100, 10);
    timeTestStrassenAlgorithm(100, 100, 10);
    timeTestRegularMultiplication(10);
    timeLinearRegression(5, 10, 10);
*/

    return 0;
}