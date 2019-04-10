#include "NotValueModelException.h"


namespace fuzzylogic::exception {

    const std::string NotValueModelException::MESSAGE(
            "MamdaniDefuzz evaluate function require a ValueModelExpression for the second parameter\n");

    const unsigned short NotValueModelException::ERROR_CODE = 6;

    NotValueModelException::NotValueModelException() : FuzzyException(MESSAGE, ERROR_CODE) {

    }
}