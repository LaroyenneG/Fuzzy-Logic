
#include "NotBinaryShadowExpressionException.h"

namespace fuzzylogic::exception {

    const std::string NotBinaryShadowExpressionException::MESSAGE(
            "SugenoDefuzz evaluate function require a BinaryShadowExpression as \n");

    const unsigned short NotBinaryShadowExpressionException::ERROR_CODE = 10;

    NotBinaryShadowExpressionException::NotBinaryShadowExpressionException() : FuzzyException(MESSAGE, ERROR_CODE) {

    }
}