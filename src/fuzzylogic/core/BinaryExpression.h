#ifndef LOGIQUEFLOUE_BINARYEXPRESSION_H
#define LOGIQUEFLOUE_BINARYEXPRESSION_H

#include "Expression.h"
#include "CoreObject.h"

namespace fuzzylogic::core {

    template<typename T>
    class BinaryExpression : public CoreObject<T> {

    public:
        virtual T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const = 0;

        virtual ~BinaryExpression() = default;
    };
}


#endif //LOGIQUEFLOUE_BINARYEXPRESSION_H
