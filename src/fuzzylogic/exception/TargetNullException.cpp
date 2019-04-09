#include "TargetNullException.h"

namespace exception {

    const std::string TargetNullException::MESSAGE(
            "The required target has been null\n" + InvalidObjectConfigurationException::MESSAGE);

    const unsigned short TargetNullException::ERROR_CODE = 2;

    TargetNullException::TargetNullException() : InvalidObjectConfigurationException(MESSAGE, ERROR_CODE) {

    }
}