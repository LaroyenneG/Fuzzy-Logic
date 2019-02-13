#ifndef LOGIQUEFLOUE_BINARYEXPRESSION_H
#define LOGIQUEFLOUE_BINARYEXPRESSION_H

#include "Expression.h"

namespace core {
    template<typename T>
    class BinaryExpression {
    public:
        virtual T evaluate(const Expression <T> *left, const Expression <T> *right) const = 0;
    };
}


#endif //LOGIQUEFLOUE_BINARYEXPRESSION_H
