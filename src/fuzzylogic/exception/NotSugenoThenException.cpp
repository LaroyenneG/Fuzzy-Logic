#include "NotSugenoThenException.h"

namespace fuzzylogic::exception {


    const std::string NotSugenoThenException::MESSAGE(
            "SugenoDefuzz evaluate function require a SugenoThen as target in BinaryShadowExpression as operator in BinaryExpressionModel\n");

    const unsigned short NotSugenoThenException::ERROR_CODE = 9;

    NotSugenoThenException::NotSugenoThenException() : FuzzyException(MESSAGE, ERROR_CODE) {

    }
}