#include "OperatorNullException.h"

namespace fuzzylogic::exception {

    const std::string OperatorNullException::MESSAGE(
            "The required operator has been null\n" + InvalidObjectConfigurationException::MESSAGE);

    const unsigned short OperatorNullException::ERROR_CODE = 1;

    OperatorNullException::OperatorNullException() : InvalidObjectConfigurationException(MESSAGE, ERROR_CODE) {

    }
}