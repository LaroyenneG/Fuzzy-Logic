#ifndef LOGIQUEFLOUE_FUZZYMONITOR_H
#define LOGIQUEFLOUE_FUZZYMONITOR_H


#include "AbstractInterpreter.h"

namespace fuzzylogic::interpreter {

    template<typename T>
    class FuzzyInterpreter : public AbstractInterpreter<T> {

    public:
        void execute(const std::string &line) override;
    };

    template<typename T>
    void FuzzyInterpreter<T>::execute(const std::string &line) {

    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H
