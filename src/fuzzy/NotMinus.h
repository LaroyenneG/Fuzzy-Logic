#ifndef LOGIQUEFLOUE_NOTMINUS_H
#define LOGIQUEFLOUE_NOTMINUS_H

#include "Not.h"

namespace fuzzy {

    template<typename T>
    class NotMinus : public Not<T> {

    public:
        T evaluate(core::Expression<T> *operand) const override;
    };

    template<typename T>
    T NotMinus<T>::evaluate(core::Expression<T> *operand) const {

        T value = operand->evaluate();

        return core::Expression<T>::ONE - value;
    }
}

#endif //LOGIQUEFLOUE_NOTMINUS_H
