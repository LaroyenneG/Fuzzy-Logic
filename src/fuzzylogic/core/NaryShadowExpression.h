#ifndef LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "NaryExpression.h"

namespace fuzzylogic::core {

    template<typename T>
    class NaryShadowExpression : public NaryExpression<T> {

    private:
        NaryExpression<T> *target;

    public:
        explicit NaryShadowExpression(NaryExpression<T> *_target);

        T evaluate(const std::vector<Expression<T> *> &operands) const override;

        const NaryExpression<T> *getTarget() const;

        void setTarget(NaryExpression<T> *_target);
    };

    template<typename T>
    NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T> *_target) : target(_target) {
    }

    template<typename T>
    T NaryShadowExpression<T>::evaluate(const std::vector<Expression<T> *> &operands) const {

        if (target == nullptr) {
            throw fuzzylogic::exception::TargetNullException();
        }

        return target->evaluate(operands);
    }

    template<typename T>
    const NaryExpression<T> *NaryShadowExpression<T>::getTarget() const {
        return target;
    }

    template<typename T>
    void NaryShadowExpression<T>::setTarget(NaryExpression<T> *_target) {
        target = _target;
    }
}


#endif //LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
