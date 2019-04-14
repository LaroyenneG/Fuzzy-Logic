#ifndef LOGIQUEFLOUE_SUGENOTHEN_H
#define LOGIQUEFLOUE_SUGENOTHEN_H

#define SUGENO_THEN_DEFAULT_PREMISE_VALUE 0

#include "ThenMult.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class SugenoThen : public ThenMult<T> {

    private:
        mutable T premiseValue;

    public:
        explicit SugenoThen(const T &_permitValue);

        explicit SugenoThen();

        const T &getPremiseValue() const;

        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    SugenoThen<T>::SugenoThen() : SugenoThen(SUGENO_THEN_DEFAULT_PREMISE_VALUE) {
    }

    template<typename T>
    SugenoThen<T>::SugenoThen(const T &_permitValue) : premiseValue(_permitValue) {
    }

    template<typename T>
    const T &SugenoThen<T>::getPremiseValue() const {

        return premiseValue;
    }

    template<typename T>
    T SugenoThen<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        premiseValue = left->evaluate();

        return ThenMult<T>::evaluate(left, right);
    }
}

#endif //LOGIQUEFLOUE_SUGENOTHEN_H
