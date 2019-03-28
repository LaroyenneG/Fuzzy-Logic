#ifndef LOGIQUEFLOUE_ORMAX_H
#define LOGIQUEFLOUE_ORMAX_H

#include "Or.h"

namespace fuzzy {
    template<typename T>
    class OrMax : public Or<T> {
    public:
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T OrMax<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return (leftValue >= rightValue) ? leftValue : rightValue;
    }
}

#endif //LOGIQUEFLOUE_ORMAX_H
