#ifndef LOGIQUEFLOUE_NOTMINUS1_H
#define LOGIQUEFLOUE_NOTMINUS1_H

#include "Not.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class NotMinus1 : public Not<T> {

    public:
        T evaluate(fuzzylogic::core::Expression<T> *operand) const override;
    };

    template<typename T>
    T NotMinus1<T>::evaluate(fuzzylogic::core::Expression<T> *operand) const {

        static const T ONE(1);

        return ONE - operand->evaluate();
    }
}

#endif //LOGIQUEFLOUE_NOTMINUS1_H
