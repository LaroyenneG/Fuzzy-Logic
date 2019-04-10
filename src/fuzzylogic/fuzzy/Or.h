#ifndef LOGIQUEFLOUE_OR_H
#define LOGIQUEFLOUE_OR_H

#include "Expression.h"
#include "BinaryExpression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class Or : public fuzzylogic::core::BinaryExpression<T> {

    public:
        virtual T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const = 0;
    };
}


#endif //LOGIQUEFLOUE_OR_H
