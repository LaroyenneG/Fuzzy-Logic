#ifndef LOGIQUEFLOUE_ANDMULT_H
#define LOGIQUEFLOUE_ANDMULT_H

#include "And.h"

namespace fuzzy {

    template<typename T>
    class AndMult : public And<T> {
    public:
        T evaluate(const Expression<T> *left, const Expression<T> *right) const;
    };

    template<typename T>
    T AndMult<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {
        T l = left->evaluate();
        T r = right->evaluate();

        return (l * r);
    }

}

#endif //LOGIQUEFLOUE_ANDMULT_H
