#ifndef LOGIQUEFLOUE_AGGMAX_H
#define LOGIQUEFLOUE_AGGMAX_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy {
    template<typename T>
    class AggMax : public Agg<T> {

    public :
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T AggMax<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return (leftValue >= rightValue) ? leftValue : rightValue;

    }
}
#endif //LOGIQUEFLOUE_AGGMAX_H
