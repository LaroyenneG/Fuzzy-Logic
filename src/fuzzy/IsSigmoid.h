#ifndef LOGIQUEFLOUE_ISSIGMOID_H
#define LOGIQUEFLOUE_ISSIGMOID_H

#include <cmath>

#include "Is.h"

#define SIGMOID_DEFAULT_MINIMUM 0

namespace fuzzy {

    template<typename T>
    class IsSigmoid : public Is<T> {

    private:
        const static T ONE;

        T min;

    public:
        explicit IsSigmoid(const T &_min);

        explicit IsSigmoid();

        void setMin(const T &_min);

        const T &getMin() const;

        T evaluate(const core::Expression<T> *expression) const;
    };

    template<typename T>
    const T IsSigmoid<T>::ONE(1);

    template<typename T>
    IsSigmoid<T>::IsSigmoid(const T &_min)
            : min(_min) {

    }

    template<typename T>
    IsSigmoid<T>::IsSigmoid()
            : IsSigmoid(SIGMOID_DEFAULT_MINIMUM) {

    }

    template<typename T>
    void IsSigmoid<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    const T &IsSigmoid<T>::getMin() const {
        return min;
    }

    template<typename T>
    T IsSigmoid<T>::evaluate(const core::Expression<T> *expression) const {

        T value = expression->evaluate();

        return ONE / (ONE + std::exp(-value - min));
    }
}


#endif //LOGIQUEFLOUE_ISSIGMOID_H