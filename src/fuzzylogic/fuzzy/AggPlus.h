#ifndef LOGIQUEFLOUE_AGGPLUS_H
#define LOGIQUEFLOUE_AGGPLUS_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy {
    template<typename T>
    class AggPlus : public Agg<T> {

    public :
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T AggPlus<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue + rightValue - leftValue * rightValue;
    }
}
#endif //LOGIQUEFLOUE_AGGPLUS_H
