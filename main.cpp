#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "Headers/doctest.h"

using namespace std::chrono;
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
    // Бенчмаркінг
    auto start = high_resolution_clock::now();
    // Тут те, що тестуємо
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    return 0;
}
