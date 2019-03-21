
#include "AbstractInterpreter.h"


namespace interpreter {

    void AbstractInterpreter::execute(std::fstream fstream) {

        std::string line;
        while (std::getline(fstream, line)) {
            execute(line);
        }
    }
}