#ifndef LOGIQUEFLOUE_THENMULT_H
#define LOGIQUEFLOUE_THENMULT_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMult : public Then<T> {

    public:
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMult<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue * rightValue;
    }
}

#endif //LOGIQUEFLOUE_THENMULT_H