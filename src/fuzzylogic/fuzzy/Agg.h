#ifndef LOGIQUEFLOUE_AGG_H
#define LOGIQUEFLOUE_AGG_H

#include "Expression.h"
#include "BinaryExpression.h"

namespace fuzzy {

    template<typename T>
    class Agg : public core::BinaryExpression<T> {

    public:
        virtual T evaluate(core::Expression<T> *left, core::Expression<T> *right) const = 0;
    };
}

#endif //LOGIQUEFLOUE_AGG_H