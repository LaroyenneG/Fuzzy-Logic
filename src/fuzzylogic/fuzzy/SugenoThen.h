#ifndef LOGIQUEFLOUE_SUGENOTHEN_H
#define LOGIQUEFLOUE_SUGENOTHEN_H

#include "Then.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class SugenoThen : public ThenMult<T> {

    private:
        const T permitValue;

    public:
        const T &getPermitValue() const;

        explicit SugenoThen(const T &_permitValue);

        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    SugenoThen<T>::SugenoThen(const T &_permitValue) : permitValue(_permitValue) {
    }

    template<typename T>
    const T &SugenoThen<T>::getPermitValue() const {
        return permitValue;
    }

    template<typename T>
    T SugenoThen<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {
        return ThenMult<T>::evaluate(left, right);
    }
}

#endif //LOGIQUEFLOUE_SUGENOTHEN_H
