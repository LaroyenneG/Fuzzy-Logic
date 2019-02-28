#ifndef LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "NaryExpression.h"

namespace core {

    template<typename T>
    class NaryShadowExpression : public NaryExpression<T> {

    private:
        const NaryExpression<T> *target;

    public:
        explicit NaryShadowExpression(NaryExpression<T> *_target);

        T evaluate(const Expression<T> **operands) const;
    };

    template<typename T>
    NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T> *_target) : target(_target) {
    }

    template<typename T>
    T NaryShadowExpression<T>::evaluate(const Expression<T> **operands) const {

        if (target == nullptr) {
            throw exception::TargetNullException();
        }

        return target->evaluate(operands);
    }
}


#endif //LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
