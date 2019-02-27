#ifndef LOGIQUEFLOUE_OR_H
#define LOGIQUEFLOUE_OR_H

#include "BinaryExpression.h"

namespace fuzzy {
    template<typename T>
    class Or : public core::BinaryExpression<T> {
    public:
        virtual T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const = 0;
    };

}


#endif //LOGIQUEFLOUE_OR_H
