#ifndef LOGIQUEFLOUE_ISRAMPLEFT_H
#define LOGIQUEFLOUE_ISRAMPLEFT_H

#include "Is.h"

namespace fuzzy {
    template<typename T>
    class IsRampLeft : public Is<T> {
    private:
        T min;
        T mid;
        T max;

    public:
        explicit IsRampLeft(const T &_min, const T &_mid, const T &_max);

        T evaluate(const core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);

    };

    template<typename T>
    IsRampLeft<T>::IsRampLeft(const T &_min, const T &_mid, const T &_max) : min(_min), mid(_mid), max(_max) {
    }

    template<typename T>
    T IsRampLeft<T>::evaluate(const core::Expression<T> *expression) const {

        T value = expression->evaluate();

        if (value <= min)
            return 0;
        else if (value < mid)
            return (max - value) / (max - mid);
        else if (value >= mid)
            return 1.0;
        else if (value > max)
            return 0;
        else
            return 0.0;
    }

    template<typename T>
    const T &IsRampLeft<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &IsRampLeft<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsRampLeft<T>::getMax() const {
        return max;
    }

    template<typename T>
    void IsRampLeft<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void IsRampLeft<T>::setMid(const T &_mid) {
        mid = _mid;
    }

    template<typename T>
    void IsRampLeft<T>::setMax(const T &_max) {
        max = _max;
    }
}

#endif //LOGIQUEFLOUE_ISRAMPLEFT_H
