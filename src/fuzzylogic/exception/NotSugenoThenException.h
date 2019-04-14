#ifndef LOGIQUEFLOUE_NOTSUGENOTHENEXCEPTION_H
#define LOGIQUEFLOUE_NOTSUGENOTHENEXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class NotSugenoThenException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit NotSugenoThenException();
    };
}

#endif //LOGIQUEFLOUE_NOTSUGENOTHENEXCEPTION_H
