#ifndef LOGIQUEFLOUE_ISRANGEBELL_H
#define LOGIQUEFLOUE_ISRANGEBELL_H

#include <cmath>
#include "Is.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class IsRangeBell : public Is<T> {

    private:
        T min;
        T mid;
        T max;
        T rangeMin;
        T rangeMax;

    public:
        explicit IsRangeBell(const T &_min, const T &_mid, const T &_max, const T &_rangeMin, const T &_rangeMax);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        const T &getRangeMin() const;

        const T &getRangeMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);

        void setRangeMin(const T &_min);

        void setRangeMax(const T &_max);

    };


    template<typename T>
    IsRangeBell<T>::IsRangeBell(const T &_min, const T &_mid, const T &_max, const T &_rangeMin, const T &_rangeMax)
            : min(_min), mid(_mid), max(_max), rangeMin(_rangeMin), rangeMax(_rangeMax) {

    }

    template<typename T>
    T IsRangeBell<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        static const T ZERO(0);
        static const T ONE(1);
        static const T TWO(2);

        T value = expression->evaluate();

        if (value < rangeMin) {

            return ZERO;

        } else if (value > rangeMax) {

            return ZERO;
        }

        return ONE / (ONE + pow(fabs((value - max) / min), (TWO * mid)));
    }

    template<typename T>
    const T &IsRangeBell<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &IsRangeBell<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsRangeBell<T>::getMax() const {
        return max;
    }

    template<typename T>
    const T &IsRangeBell<T>::getRangeMax() const {
        return rangeMax;
    }

    template<typename T>
    const T &IsRangeBell<T>::getRangeMin() const {
        return rangeMin;
    }

    template<typename T>
    void IsRangeBell<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void IsRangeBell<T>::setMid(const T &_mid) {
        mid = _mid;
    }

    template<typename T>
    void IsRangeBell<T>::setMax(const T &_max) {
        max = _max;
    }

    template<typename T>
    void IsRangeBell<T>::setRangeMax(const T &_max) {
        rangeMax = _max;
    }

    template<typename T>
    void IsRangeBell<T>::setRangeMin(const T &_min) {
        rangeMin = _min;
    }

}
#endif //LOGIQUEFLOUE_ISRANGEBELL_H
