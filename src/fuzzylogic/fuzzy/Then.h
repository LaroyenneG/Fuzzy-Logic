#ifndef LOGIQUEFLOUE_THEN_H
#define LOGIQUEFLOUE_THEN_H

#include "BinaryExpression.h"
#include "Expression.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class Then : public fuzzylogic::core::BinaryExpression<T> {

    public:
        virtual T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const = 0;
    };
}

#endif //LOGIQUEFLOUE_THEN_H
