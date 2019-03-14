#ifndef LOGIQUEFLOUE_THENMULT_H
#define LOGIQUEFLOUE_THENMULT_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMult : public Then<T> {

    public:
        virtual T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMult<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue * rightValue;
    }
}

#endif //LOGIQUEFLOUE_THENMULT_H