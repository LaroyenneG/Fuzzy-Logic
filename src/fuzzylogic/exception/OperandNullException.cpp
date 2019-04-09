#include "OperandNullException.h"

namespace exception {

    const std::string OperandNullException::MESSAGE(
            "The required operand has been null\n" + InvalidObjectConfigurationException::MESSAGE);

    const unsigned short OperandNullException::ERROR_CODE = 2;

    OperandNullException::OperandNullException() : InvalidObjectConfigurationException(MESSAGE, ERROR_CODE) {
    }
}