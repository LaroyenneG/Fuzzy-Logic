#ifndef LOGIQUEFLOUE_THENMIN_H
#define LOGIQUEFLOUE_THENMIN_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMin : public Then<T> {
    public:
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMin<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return (leftValue <= rightValue) ? leftValue : rightValue;
    }
}


#endif //LOGIQUEFLOUE_THENMIN_H