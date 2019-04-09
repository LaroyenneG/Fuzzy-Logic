#ifndef LOGIQUEFLOUE_NARYEXPRESSION_H
#define LOGIQUEFLOUE_NARYEXPRESSION_H

#include <vector>
#include "Expression.h"

namespace fuzzylogic::core {

    template<typename T>
    class NaryExpression {

    public:
        virtual T evaluate(const std::vector<Expression<T> *> &operands) const = 0;
    };
}

#endif //LOGIQUEFLOUE_NARYEXPRESSION_H
