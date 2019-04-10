#ifndef LOGIQUEFLOUE_ISTRIANGLE_H
#define LOGIQUEFLOUE_ISTRIANGLE_H

#include "Expression.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class IsTriangle : public Is<T> {

    private:
        T min;
        T mid;
        T max;

    public:
        explicit IsTriangle(const T &_min, const T &_mid, const T &_max);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);
    };

    template<typename T>
    IsTriangle<T>::IsTriangle(const T &_min, const T &_mid, const T &_max) : min(_min), mid(_mid), max(_max) {
    }

    template<typename T>
    T IsTriangle<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        T value = expression->evaluate();

        if (value <= min)
            return (value - value);
        else if (value >= min && value <= mid)
            return (value - min) / (mid - min);
        else if (value >= mid && value <= max)
            return (max - value) / (max - mid);
        return 0;

        //return (value <= mid) ? (value - min) / (mid - min) : (max - value) / (max - min);
    }

    template<typename T>
    const T &IsTriangle<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &IsTriangle<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsTriangle<T>::getMax() const {
        return max;
    }

    template<typename T>
    void IsTriangle<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void IsTriangle<T>::setMid(const T &_mid) {
        mid = _mid;
    }

    template<typename T>
    void IsTriangle<T>::setMax(const T &_max) {
        max = _max;
    }
}

#endif //LOGIQUEFLOUE_ISTRIANGLE_H
