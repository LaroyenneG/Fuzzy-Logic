
#ifndef LOGIQUEFLOUE_NOTBINARYSHADOWEXPRESSIONEXCEPTION_H
#define LOGIQUEFLOUE_NOTBINARYSHADOWEXPRESSIONEXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class NotBinaryShadowExpressionException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit NotBinaryShadowExpressionException();

    };
}

#endif //LOGIQUEFLOUE_NOTBINARYSHADOWEXPRESSIONEXCEPTION_H
