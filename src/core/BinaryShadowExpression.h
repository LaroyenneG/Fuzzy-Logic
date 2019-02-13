#ifndef LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H

#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryShadowExpression : public BinaryExpression<T> {
    public:
        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;

    private:
        T *target;
    };

    template<typename T>
    T BinaryShadowExpression<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {
        if (target != nullptr) {
            return target.evaluate(*left, *right);
        }
        return nullptr;
    }
}


#endif //LOGIQUEFLOUE_BINARYSHADOWEXPRESSION_H
