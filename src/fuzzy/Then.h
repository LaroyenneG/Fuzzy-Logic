#ifndef LOGIQUEFLOUE_THEN_H
#define LOGIQUEFLOUE_THEN_H

#include "BinaryExpression.h"
#include "Expression.h"

namespace fuzzy {

    template<typename T>
    class Then : public core::BinaryExpression<T> {

    public:
        virtual T evaluate(core::Expression<T> *left, core::Expression<T> *right) const = 0;
    };
}

#endif //LOGIQUEFLOUE_THEN_H
