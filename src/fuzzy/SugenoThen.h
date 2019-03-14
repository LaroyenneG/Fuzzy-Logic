#ifndef LOGIQUEFLOUE_SUGENOTHEN_H
#define LOGIQUEFLOUE_SUGENOTHEN_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class SugenoThen : public Then<T> {

    private:
        const T permiseValue;

    public:
        const T &getPermiseValue() const;

        explicit SugenoThen(const T &_permiseValue);

        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    SugenoThen<T>::SugenoThen(const T &_permiseValue) : permiseValue(_permiseValue) {

    }

    template<typename T>
    T SugenoThen<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {

        T leftValue = left->evaluate();
        T rightValue = right->evaluate();

        return leftValue * rightValue;
    }

    template<typename T>
    const T &SugenoThen<T>::getPermiseValue() const {
        return permiseValue;
    }
}

#endif //LOGIQUEFLOUE_SUGENOTHEN_H
