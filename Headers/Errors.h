#ifndef ALGORITHMSGROUPPROJECTLU_ERRORS_H
#define ALGORITHMSGROUPPROJECTLU_ERRORS_H

#include <map>
#include <iostream>

using std::cout;
using std::endl;
using std::map;

// Коди помилок
const int MATRIX_IS_NOT_SQUARE_ERROR_CODE = 1;

const int CANNOT_DIVIDE_BY_ZERO_ERROR_CODE = 2;

const int CANNOT_ADD_OR_SUBTRACT_ERROR_CODE = 3;

const int CANNOT_MULTIPLY_ERROR_CODE = 4;

const int CANNOT_FIND_INVERSE_MATRIX_ERROR_CODE = 5;

const int CANNOT_FIND_LU_DECOMPOSITION_ERROR_CODE = 6;

const int CANNOT_BUILD_LINEAR_REGRESSION_ERROR_CODE = 7;

// Текст помилок
const char* MATRIX_IS_NOT_SQUARE_ERROR_TEXT = "MATRIX IS NOT SQUARE";

const char* CANNOT_DIVIDE_BY_ZERO_ERROR_TEXT = "CANNOT DIVIDE BY ZERO";

const char* CANNOT_ADD_OR_SUBTRACT_ERROR_TEXT = "CANNOT ADD OR SUBTRACT MATRICES OF DIFFERENT DIMENSIONS";

const char* CANNOT_MULTIPLY_ERROR_TEXT = "CANNOT MULTIPLY MATRICES OF DIFFERENT DIMENSIONS";

const char* CANNOT_FIND_INVERSE_MATRIX_ERROR_TEXT = "MATRIX IS NOT INVERTIBLE";

const char* CANNOT_FIND_LU_DECOMPOSITION_ERROR_TEXT = "CANNOT FIND LU DECOMPOSITION";

const char* CANNOT_BUILD_LINEAR_REGRESSION_ERROR_TEXT = "WRONG MATRICES DIMENSIONS FOR BUILDING LINEAR REGRESSION";

map<int, const char*> ERRORS_MAP = {
    {MATRIX_IS_NOT_SQUARE_ERROR_CODE, MATRIX_IS_NOT_SQUARE_ERROR_TEXT},
    {CANNOT_DIVIDE_BY_ZERO_ERROR_CODE, CANNOT_DIVIDE_BY_ZERO_ERROR_TEXT},
    {CANNOT_ADD_OR_SUBTRACT_ERROR_CODE, CANNOT_ADD_OR_SUBTRACT_ERROR_TEXT},
    {CANNOT_MULTIPLY_ERROR_CODE, CANNOT_MULTIPLY_ERROR_TEXT},
    {CANNOT_FIND_INVERSE_MATRIX_ERROR_CODE, CANNOT_FIND_INVERSE_MATRIX_ERROR_TEXT},
    {CANNOT_FIND_LU_DECOMPOSITION_ERROR_CODE, CANNOT_FIND_LU_DECOMPOSITION_ERROR_TEXT},
    {CANNOT_BUILD_LINEAR_REGRESSION_ERROR_CODE, CANNOT_BUILD_LINEAR_REGRESSION_ERROR_TEXT}
};

void printError(int error) {
    cout << "ERROR " << error << ": " << ERRORS_MAP[error] << endl;
}

#endif //ALGORITHMSGROUPPROJECTLU_ERRORS_H