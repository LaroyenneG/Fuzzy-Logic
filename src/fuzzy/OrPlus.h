#ifndef LOGIQUEFLOUE_ORPLUS_H
#define LOGIQUEFLOUE_ORPLUS_H

#include "Or.h"

namespace fuzzy {

    template<typename T>
    class OrPlus : public core::BinaryExpression<T> {

    public:
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T OrPlus<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue + rightValue - leftValue * rightValue;
    }
}

#endif //LOGIQUEFLOUE_ORPLUS_H
