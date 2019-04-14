#ifndef LOGIQUEFLOUE_NOTVALUEMODELEXCEPTION_H
#define LOGIQUEFLOUE_NOTVALUEMODELEXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class NotValueModelException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit NotValueModelException();
    };
}


#endif //LOGIQUEFLOUE_NOTVALUEMODELEXCEPTION_H
