#ifndef LOGIQUEFLOUE_UNARYEXPRESSION_H
#define LOGIQUEFLOUE_UNARYEXPRESSION_H

#include "Expression.h"

namespace core {
    template<typename T>
    class UnaryExpression {
        virtual T evaluate(const Expression<T> *expression) const = 0;
    };
}


#endif //LOGIQUEFLOUE_UNARYEXPRESSION_H
