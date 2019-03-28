#ifndef LOGIQUEFLOUE_THENMIN_H
#define LOGIQUEFLOUE_THENMIN_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMin : public Then<T> {
    public:
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMin<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return (leftValue <= rightValue) ? leftValue : rightValue;
    }
}


#endif //LOGIQUEFLOUE_THENMIN_H