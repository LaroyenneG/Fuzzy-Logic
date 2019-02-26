#ifndef LOGIQUEFLOUE_NARYEXPRESSION_H
#define LOGIQUEFLOUE_NARYEXPRESSION_H

#include "Expression.h"

namespace core {

    template<typename T>
    class NaryExpression {

    public:
        virtual T evaluate(const Expression<T> **operands) const = 0;
    };
}

#endif //LOGIQUEFLOUE_NARYEXPRESSION_H
