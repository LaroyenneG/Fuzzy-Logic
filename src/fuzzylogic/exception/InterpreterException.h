

#ifndef FUZZY_LOGIC_INTERPRETEREXCEPTION_H
#define FUZZY_LOGIC_INTERPRETEREXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class InterpreterException : public FuzzyException {

    private:
        static const std::string MESSAGE;
        static const unsigned short ERROR_CODE;


    public:
        explicit InterpreterException(const std::string &msg);
    };
}

#endif //FUZZY_LOGIC_INTERPRETEREXCEPTION_H
