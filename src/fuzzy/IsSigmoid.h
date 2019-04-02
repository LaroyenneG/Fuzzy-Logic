#ifndef LOGIQUEFLOUE_ISSIGMOID_H
#define LOGIQUEFLOUE_ISSIGMOID_H

#include <cmath>

#include "Is.h"

#define SIGMOID_DEFAULT_MINIMUM 0

namespace fuzzy {

    template<typename T>
    class IsSigmoid : public Is<T> {

    private:
        T min;

    public:
        explicit IsSigmoid(const T &_min);

        explicit IsSigmoid();

        void setMin(const T &_min);

        const T &getMin() const;

        T evaluate(core::Expression<T> *expression) const override;
    };

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
    T IsSigmoid<T>::evaluate(core::Expression<T> *expression) const {

        T value = expression->evaluate();

        return core::Expression<T>::ONE / (core::Expression<T>::ONE + std::exp(-value - min));
    }
}


#endif //LOGIQUEFLOUE_ISSIGMOID_H
