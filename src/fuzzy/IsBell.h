#ifndef LOGIQUEFLOUE_ISBELL_H
#define LOGIQUEFLOUE_ISBELL_H

#include <cmath>
#include "Is.h"

namespace fuzzy {
    template<typename T>
    class IsBell : public Is<T> {
    private:
        T min;
        T mid;
        T max;

    public:
        explicit IsBell(const T &_min, const T &_mid, const T &_max);

        T evaluate(const core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);

    };

    template<typename T>
    IsBell<T>::IsBell(const T &_min, const T &_mid, const T &_max) : min(_min), mid(_mid), max(_max) {

    }

    template<typename T>
    T IsBell<T>::evaluate(const core::Expression<T> *expression) const {
        T value = expression->evaluate();
        return 1 / (1 + pow(abs((value - max) / min), (2 * mid)));
    }

    template<typename T>
    const T &IsBell<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &IsBell<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsBell<T>::getMax() const {
        return max;
    }

    template<typename T>
    void IsBell<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void IsBell<T>::setMid(const T &_mid) {
        mid = _mid;
    }

    template<typename T>
    void IsBell<T>::setMax(const T &_max) {
        max = _max;
    }

}
#endif //LOGIQUEFLOUE_ISBELL_H
