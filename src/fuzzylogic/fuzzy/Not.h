#ifndef LOGIQUEFLOUE_NOT_H
#define LOGIQUEFLOUE_NOT_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace fuzzy {
    template<typename T>
    class Not : public core::UnaryExpression<T> {

    public:
        virtual T evaluate(core::Expression<T> *operand) const = 0;
    };

}
#endif //LOGIQUEFLOUE_NOT_H
