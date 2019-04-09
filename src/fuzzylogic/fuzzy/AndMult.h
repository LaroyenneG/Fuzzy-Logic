#ifndef LOGIQUEFLOUE_ANDMULT_H
#define LOGIQUEFLOUE_ANDMULT_H

#include "And.h"
#include "Expression.h"

namespace fuzzy {
    template<typename T>
    class AndMult : public And<T> {

    public:
        T evaluate(core::Expression<T> *left, core::Expression<T> *right) const override;
    };

    template<typename T>
    T AndMult<T>::evaluate(core::Expression<T> *left, core::Expression<T> *right) const {

        T l = left->evaluate();
        T r = right->evaluate();

        return l * r;
    }
}

#endif //LOGIQUEFLOUE_ANDMULT_H
