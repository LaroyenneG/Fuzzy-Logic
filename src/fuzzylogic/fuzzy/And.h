#ifndef LOGIQUEFLOUE_AND_H
#define LOGIQUEFLOUE_AND_H

#include "Expression.h"
#include "BinaryExpression.h"


namespace fuzzylogic::fuzzy {
    template<typename T>
    class And : public fuzzylogic::core::BinaryExpression<T> {

    public:
        virtual T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const = 0;
    };
}

#endif //LOGIQUEFLOUE_AND_H
