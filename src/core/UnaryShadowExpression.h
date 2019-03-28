#ifndef LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryShadowExpression : public UnaryExpression<T> {

    private:
        UnaryExpression<T> *target;

    public:
        explicit UnaryShadowExpression(UnaryExpression <T> *_target);

        T evaluate(Expression <T> *expression) const override;

        const UnaryExpression<T> *getTarget() const;

        void setTarget(UnaryExpression<T> *_target);
    };

    template<typename T>
    UnaryShadowExpression<T>::UnaryShadowExpression(UnaryExpression <T> *_target) : target(_target) {
    }

    template<typename T>
    T UnaryShadowExpression<T>::evaluate(Expression <T> *expression) const {

        if (target == nullptr) {
            throw exception::TargetNullException();
        }

        return target->evaluate(expression);
    }

    template<typename T>
    const UnaryExpression<T> *UnaryShadowExpression<T>::getTarget() const {
        return target;
    }

    template<typename T>
    void UnaryShadowExpression<T>::setTarget(UnaryExpression<T> *_target) {
        target = _target;
    }
}


#endif //LOGIQUEFLOUE_UNARYSHADOWEXPRESSION_H
