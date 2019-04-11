#ifndef LOGIQUEFLOUE_UNARYEXPRESSION_H
#define LOGIQUEFLOUE_UNARYEXPRESSION_H

#include "Expression.h"

namespace fuzzylogic::core {
    template<typename T>
    class UnaryExpression {
    public:
        virtual T evaluate(Expression <T> *expression) const = 0;

        virtual ~UnaryExpression() = default;
    };
}


#endif //LOGIQUEFLOUE_UNARYEXPRESSION_H
