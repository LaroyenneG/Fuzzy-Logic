#ifndef LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H

#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryShadowExpression : public UnaryExpression<T> {
    public:
        T evaluate(const Expression<T> *expression) const override;

    private:
        UnaryExpression<T> *target;
    };

    template<typename T>
    T UnaryShadowExpression<T>::evaluate(const Expression<T> *expression) const {
        if (target != nullptr) {
            return target->evaluate(expression);
        }
        return 0;
    }
}


#endif //LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
