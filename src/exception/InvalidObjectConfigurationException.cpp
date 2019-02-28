#include "InvalidObjectConfigurationException.h"

namespace exception {

    const std::string InvalidObjectConfigurationException::MESSAGE(
            "You have activated a function with a invalid configuration.\nPlease use a other constructor to escape this error");

    InvalidObjectConfigurationException::InvalidObjectConfigurationException(const std::string &_message,
                                                                             unsigned short _errorCode)
            : FuzzyException(_message, _errorCode) {
    }
}