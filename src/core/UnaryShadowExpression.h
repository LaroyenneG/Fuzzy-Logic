#ifndef LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryShadowExpression : public UnaryExpression<T> {

    private:
        const UnaryExpression<T> *target;

    public:
        explicit UnaryShadowExpression(const UnaryExpression<T> *_target);

        T evaluate(const Expression<T> *expression) const override;
    };

    template<typename T>
    UnaryShadowExpression<T>::UnaryShadowExpression(const UnaryExpression<T> *_target) : target(_target) {
    }

    template<typename T>
    T UnaryShadowExpression<T>::evaluate(const Expression<T> *expression) const {

        if (target != nullptr) {
            throw exception::TargetNullException();
        }

        return target->evaluate(expression);
    }
}


#endif //LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
