#ifndef LOGIQUEFLOUE_ORMAX_H
#define LOGIQUEFLOUE_ORMAX_H

#include "Or.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class OrMax : public Or<T> {
    public:
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T OrMax<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return (leftValue >= rightValue) ? leftValue : rightValue;
    }
}

#endif //LOGIQUEFLOUE_ORMAX_H
