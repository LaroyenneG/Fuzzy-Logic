#ifndef LOGIQUEFLOUE_MAMDANIDEFUZZ_H
#define LOGIQUEFLOUE_MAMDANIDEFUZZ_H

#include "BinaryExpression.h"
#include "Shape.h"

namespace fuzzy {

    template<typename T>
    class MamdaniDefuzz : public core::BinaryExpression<T> {

        virtual T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const;

        virtual T defuzz(const Shape<T> *shape) = 0;
    };

    template<typename T>
    T MamdaniDefuzz<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return 0;
    }
}


#endif //LOGIQUEFLOUE_MAMDANIDEFUZZ_H
