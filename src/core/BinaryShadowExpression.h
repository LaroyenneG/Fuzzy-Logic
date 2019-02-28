#ifndef LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H

#include "TargetNullException.h"
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryShadowExpression : public BinaryExpression<T> {

    private:
        const BinaryExpression<T> *target;

    public:
        explicit BinaryShadowExpression(const BinaryExpression<T> *_target);

        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;
    };

    template<typename T>
    BinaryShadowExpression<T>::BinaryShadowExpression(const BinaryExpression<T> *_target) : target(_target) {

    }

    template<typename T>
    T BinaryShadowExpression<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {

        if (target == nullptr) {
            throw exception::TargetNullException();
        }

        return target->evaluate(left, right);
    }
}


#endif //LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
