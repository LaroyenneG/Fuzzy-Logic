#ifndef LOGIQUEFLOUE_IS_H
#define LOGIQUEFLOUE_IS_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace fuzzy {

    template<typename T>
    class Is : public core::UnaryExpression<T> {

    public:
        virtual T evaluate(core::Expression<T> *expression) const = 0;
    };
}

#endif //LOGIQUEFLOUE_IS_H
