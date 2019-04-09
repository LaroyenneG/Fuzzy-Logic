#ifndef LOGIQUEFLOUE_ORPLUS_H
#define LOGIQUEFLOUE_ORPLUS_H

#include "Or.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class OrPlus : public fuzzylogic::core::BinaryExpression<T> {

    public:
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T OrPlus<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue + rightValue - leftValue * rightValue;
    }
}

#endif //LOGIQUEFLOUE_ORPLUS_H
