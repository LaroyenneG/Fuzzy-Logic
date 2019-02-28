#ifndef LOGIQUEFLOUE_EXPRESSIONNULLEXCEPTION_H
#define LOGIQUEFLOUE_EXPRESSIONNULLEXCEPTION_H


#include "InvalidObjectConfigurationException.h"

namespace exception {

    class OperandNullException : public InvalidObjectConfigurationException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit OperandNullException();
    };
}


#endif //LOGIQUEFLOUE_EXPRESSIONNULLEXCEPTION_H
