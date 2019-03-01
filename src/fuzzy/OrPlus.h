#ifndef LOGIQUEFLOUE_ORPLUS_H
#define LOGIQUEFLOUE_ORPLUS_H

#include "Or.h"

namespace fuzzy {
    template<typename T>
    class OrPlus : public core::BinaryExpression<T> {
    public:
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;

    };

    template<typename T>
    T OrPlus<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = left->evaluate();

        return leftValue + rightValue;
    }
}

#endif //LOGIQUEFLOUE_ORPLUS_H
