

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    fuzzylogic::exception::FuzzyException::FuzzyException(const std::string &_message, unsigned short _errorCode)
            : std::runtime_error(_message), time(0), errorCode(_errorCode) {
    }

    const std::string FuzzyException::getMessage() const {
        return std::string(what());
    }

    std::string FuzzyException::getTime() const {

        auto *local = std::localtime(&time);

        std::string string = std::asctime(local);

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