#ifndef LOGIQUEFLOUE_NOTBINARYEXPRESSIONMODELEXCEPTION_H
#define LOGIQUEFLOUE_NOTBINARYEXPRESSIONMODELEXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class NotBinaryExpressionModelException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        NotBinaryExpressionModelException();

    };
}

#endif //LOGIQUEFLOUE_NOTBINARYEXPRESSIONMODELEXCEPTION_H
