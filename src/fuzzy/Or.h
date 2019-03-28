#ifndef LOGIQUEFLOUE_OR_H
#define LOGIQUEFLOUE_OR_H

#include "Expression.h"
#include "BinaryExpression.h"

namespace fuzzy {
    template<typename T>
    class Or : public core::BinaryExpression<T> {

    public:
        virtual T evaluate(core::Expression<T> *left, core::Expression<T> *right) const = 0;
    };
}


#endif //LOGIQUEFLOUE_OR_H
