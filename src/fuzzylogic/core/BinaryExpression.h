#ifndef LOGIQUEFLOUE_BINARYEXPRESSION_H
#define LOGIQUEFLOUE_BINARYEXPRESSION_H

#include "Expression.h"

namespace fuzzylogic::core {

    template<typename T>
    class BinaryExpression {

    public:
        virtual T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const = 0;
    };
}


#endif //LOGIQUEFLOUE_BINARYEXPRESSION_H
