#ifndef LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryShadowExpression : public BinaryExpression<T> {

    private:
        BinaryExpression<T> *target;

    public:
        explicit BinaryShadowExpression(BinaryExpression <T> *_target);

        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;

        const BinaryExpression<T> *getTarget() const;

        void setTarget(BinaryExpression<T> *_target);
    };

    template<typename T>
    BinaryShadowExpression<T>::BinaryShadowExpression(BinaryExpression <T> *_target) : target(_target) {
    }

    template<typename T>
    T BinaryShadowExpression<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {

        if (target == nullptr) {
            throw exception::TargetNullException();
        }

        return target->evaluate(left, right);
    }

    template<typename T>
    const BinaryExpression<T> *BinaryShadowExpression<T>::getTarget() const {
        return target;
    }

    template<typename T>
    void BinaryShadowExpression<T>::setTarget(BinaryExpression<T> *_target) {
        target = _target;
    }
}


#endif //LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
