#ifndef LOGIQUEFLOUE_BINARYEXPRESSION_H
#define LOGIQUEFLOUE_BINARYEXPRESSION_H

#include "Expression.h"

namespace core {

    template<typename T>
    class BinaryExpression {

    public:
        virtual T evaluate(core::Expression<T> *left, core::Expression<T> *right) const = 0;
    };
}


#endif //LOGIQUEFLOUE_BINARYEXPRESSION_H
