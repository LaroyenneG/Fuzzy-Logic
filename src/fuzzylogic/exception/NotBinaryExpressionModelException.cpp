
#include "NotBinaryExpressionModelException.h"

namespace fuzzylogic::exception {

    const std::string NotBinaryExpressionModelException::MESSAGE(
            "SugenoDefuzz evaluate function require a BinaryExpressionModel vector as parameter\n");

    const unsigned short NotBinaryExpressionModelException::ERROR_CODE = 8;

    NotBinaryExpressionModelException::NotBinaryExpressionModelException() : FuzzyException(MESSAGE, ERROR_CODE) {

    }
}