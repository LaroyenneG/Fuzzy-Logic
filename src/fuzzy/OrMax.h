#ifndef LOGIQUEFLOUE_ORMAX_H
#define LOGIQUEFLOUE_ORMAX_H

#include "Or.h"

namespace fuzzy {
    template<typename T>
    class OrMax : public Or<T> {
    public:
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;

    };

    template<typename T>
    T OrMax<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return (left >= right) ? left : right;
    }
}

#endif //LOGIQUEFLOUE_ORMAX_H
