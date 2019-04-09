#ifndef LOGIQUEFLOUE_THENMULT_H
#define LOGIQUEFLOUE_THENMULT_H

#include "Then.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class ThenMult : public Then<T> {

    public:
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMult<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue * rightValue;
    }
}

#endif //LOGIQUEFLOUE_THENMULT_H