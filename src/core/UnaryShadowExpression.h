#ifndef LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H

#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryShadowExpression : public UnaryExpression<T> {
    public:
        T evaluate(const Expression<T> *expression) const override;
    };

    template<typename T>
    T UnaryShadowExpression<T>::evaluate(const Expression<T> *expression) const {
        return nullptr;
    }
}


#endif //LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
