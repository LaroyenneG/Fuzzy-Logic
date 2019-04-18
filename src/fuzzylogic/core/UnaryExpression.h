#ifndef LOGIQUEFLOUE_UNARYEXPRESSION_H
#define LOGIQUEFLOUE_UNARYEXPRESSION_H

#include "Expression.h"
#include "CoreObject.h"

namespace fuzzylogic::core {
    template<typename T>
    class UnaryExpression : public CoreObject<T> {
    public:
        virtual T evaluate(Expression <T> *expression) const = 0;

        virtual ~UnaryExpression() = default;
    };
}


#endif //LOGIQUEFLOUE_UNARYEXPRESSION_H
