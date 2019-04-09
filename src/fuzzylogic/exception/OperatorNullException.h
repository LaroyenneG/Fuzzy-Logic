
#ifndef LOGIQUEFLOUE_OPERANDNULLEXCEPTION_H
#define LOGIQUEFLOUE_OPERANDNULLEXCEPTION_H

#include "InvalidObjectConfigurationException.h"

namespace exception {

    class OperatorNullException : public InvalidObjectConfigurationException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit OperatorNullException();
    };
}


#endif //LOGIQUEFLOUE_OPERANDNULLEXCEPTION_H
