#ifndef FUZZY_LOGIC_AEQUAL_H
#define FUZZY_LOGIC_AEQUAL_H

#include "Or.h"

#define DEFAULT_DELTAT_VALUE 0.2

namespace fuzzylogic::fuzzy {
    template<typename T>
    class ApproximatelyEqual : public Or<T> {

    private:
        const T delta;

    public :
        explicit ApproximatelyEqual(const T &_delta);

        explicit ApproximatelyEqual();

        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T ApproximatelyEqual<T>::evaluate(fuzzylogic::core::Expression<T> *left,
                                      fuzzylogic::core::Expression<T> *right) const {

        static const T ZERO(0);

        T l = left->evaluate();
        T r = right->evaluate();

        return (abs(l - r) <= delta) ? l : ZERO;
    }

    template<typename T>
    ApproximatelyEqual<T>::ApproximatelyEqual(const T &_delta) : delta(_delta) {
    }

    template<typename T>
    ApproximatelyEqual<T>::ApproximatelyEqual() : delta(DEFAULT_DELTAT_VALUE) {
    }

}
#endif //FUZZY_LOGIC_EQUAL_H
