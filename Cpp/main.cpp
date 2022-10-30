#include "Headers/ComplexMatrix.h"
#include "Headers/Benchmarks.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "Headers/Doctest/doctest.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
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
    timeTestInverseGaussJordan();
    timeTestInverseLU();
    timeTestStrassenAlgorithm();
    return 0;
}
