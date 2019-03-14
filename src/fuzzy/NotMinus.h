#ifndef LOGIQUEFLOUE_NOTMINUS_H
#define LOGIQUEFLOUE_NOTMINUS_H

#include "Not.h"


namespace fuzzy {

    template<typename T>
    class NotMinus : public Not<T> {

    private:
        constexpr static T ONE = 1;

    public:
        T evaluate(const core::Expression<T> *operand) const override;
    };

    template<typename T>
    T NotMinus<T>::evaluate(const core::Expression<T> *operand) const {

        T op = operand->evaluate();

        return ONE - op;
    }


}

#endif //LOGIQUEFLOUE_NOTMINUS_H
