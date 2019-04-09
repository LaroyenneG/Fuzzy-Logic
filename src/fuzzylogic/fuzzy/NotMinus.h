#ifndef LOGIQUEFLOUE_NOTMINUS_H
#define LOGIQUEFLOUE_NOTMINUS_H

#include "Not.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class NotMinus : public Not<T> {

    public:
        T evaluate(fuzzylogic::core::Expression<T> *operand) const override;
    };

    template<typename T>
    T NotMinus<T>::evaluate(fuzzylogic::core::Expression<T> *operand) const {

        static const T ONE(1);

        T value = operand->evaluate();

        return ONE - value;
    }
}

#endif //LOGIQUEFLOUE_NOTMINUS_H
