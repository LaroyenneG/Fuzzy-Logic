#ifndef LOGIQUEFLOUE_AGGPLUS_H
#define LOGIQUEFLOUE_AGGPLUS_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class AggPlus : public Agg<T> {

    public :
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T AggPlus<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue + rightValue - leftValue * rightValue;
    }
}
#endif //LOGIQUEFLOUE_AGGPLUS_H
