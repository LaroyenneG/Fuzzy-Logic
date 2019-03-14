

#include "FuzzyException.h"

namespace exception {

    exception::FuzzyException::FuzzyException(const std::string &_message, unsigned short _errorCode)
            : message(_message), time(0), errorCode(_errorCode) {
    }

    const std::string &FuzzyException::getMessage() const {
        return message;
    }

    std::string FuzzyException::getTime() const {

        auto *local = std::localtime(&time);

        std::string string = std::asctime(local);

        delete local;

        return string;
    }

    unsigned short FuzzyException::getErrorCode() const {
        return errorCode;
    }

    void FuzzyException::printDebug() const {
        std::cerr << getMessage() << std::endl;
        std::cerr << "At :" << getTime() << std::endl;
        std::cerr << "Error code : " << getErrorCode() << std::endl;
    }
}