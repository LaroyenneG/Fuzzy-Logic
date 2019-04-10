//
// Created by rabougris on 3/26/19.
//

#ifndef LOGIQUEFLOUE_ISRAMPRIGHT_H
#define LOGIQUEFLOUE_ISRAMPRIGHT_H

#include "Is.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class IsRampRight : public Is<T> {
    private:
        T min;
        T mid;
        T max;

    public:
        explicit IsRampRight(const T &_min, const T &_mid, const T &_max);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);
    };

    template<typename T>
    IsRampRight<T>::IsRampRight(const T &_min, const T &_mid, const T &_max) : min(_min), mid(_mid), max(_max) {
    }

    template<typename T>
    T IsRampRight<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        static const T ONE(1);
        static const T ZERO(0);

        T value = expression->evaluate();

        if (value > mid && value < max) {

            return (max - value) / (max - mid);

        } else if (value <= mid) {

            return ONE;
        }

        return ZERO;
    }

    template<typename T>
    const T &IsRampRight<T>::getMin() const {

        return min;
    }

    template<typename T>
    const T &IsRampRight<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsRampRight<T>::getMax() const {

        return max;
    }

    template<typename T>
    void IsRampRight<T>::setMin(const T &_min) {

        min = _min;
    }

    template<typename T>
    void IsRampRight<T>::setMid(const T &_mid) {

        mid = _mid;
    }

    template<typename T>
    void IsRampRight<T>::setMax(const T &_max) {

        max = _max;
    }

}
#endif //LOGIQUEFLOUE_ISRAMPRIGHT_H
