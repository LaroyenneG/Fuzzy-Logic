#ifndef LOGIQUEFLOUE_NOTMINUS_H
#define LOGIQUEFLOUE_NOTMINUS_H

#include "Not.h"


namespace fuzzy {

    template<typename T>
    class NotMinus : public Not<T> {

    private:
        const static T ONE; // warning

    public:
        T evaluate(const core::Expression<T> *operand) const override;
    };

    template<typename T>
    T NotMinus<T>::evaluate(const core::Expression<T> *operand) const {

        T value = operand->evaluate();

        return ONE - value;
    }

    template<typename T>
    const T NotMinus<T>::ONE(1);
}

#endif //LOGIQUEFLOUE_NOTMINUS_H
