
#include "InterpreterException.h"

namespace fuzzylogic::exception {

    const std::string InterpreterException::MESSAGE("Interpreter error\n");
    const unsigned short InterpreterException::ERROR_CODE = 20;

    InterpreterException::InterpreterException(const std::string &msg) : FuzzyException(MESSAGE + msg, ERROR_CODE) {

    }
}