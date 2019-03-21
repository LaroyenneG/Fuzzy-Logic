

#ifndef LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
#define LOGIQUEFLOUE_ABSTRACTINTERPRETER_H

#include <fstream>
#include <string>

namespace interpreter {

    class AbstractInterpreter {

    public:
        virtual void execute(std::string line) = 0;

        void execute(std::fstream fstream);
    };
}

#endif //LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
