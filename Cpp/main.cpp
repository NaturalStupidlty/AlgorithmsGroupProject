#include "Headers/Benchmarks.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "Headers/Doctest/doctest.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    // Cyrillic on Windows
    #ifdef _WIN32
    system("chcp 65001");
    #endif

    // Unit tests
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int result = context.run();
    if(context.shouldExit())
    {
        return result;
    }

    // Benchmarks
    cout << "~~~~~~~~~~~~~~~~ Benchmarks ~~~~~~~~~~~~~~~~" << endl;
    timeTestInverseGaussJordan(128, 10);
    timeTestInverseLU(100, 10);
    timeTestStrassenAlgorithm(100, 100, 10);
    timeTestRegularMultiplication(100, 100, 10);
    timeLinearRegression(5, 10, 10);
    return 0;
}