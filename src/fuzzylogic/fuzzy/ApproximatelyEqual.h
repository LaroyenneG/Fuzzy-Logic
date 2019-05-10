#ifndef FUZZY_LOGIC_AEQUAL_H
#define FUZZY_LOGIC_AEQUAL_H

#include "Expression.h"
#include "Or.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class ApproximatelyEqual : public Or<T> {

    public :
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T ApproximatelyEqual<T>::evaluate(fuzzylogic::core::Expression<T> *left,
                                      fuzzylogic::core::Expression<T> *right) const {

        static const T DELTA(0.2);
        static const T ZERO(0);

        T l = left->evaluate();
        T r = right->evaluate();

        return (abs(l - r) <= DELTA) ? l : ZERO;
    }

}
#endif //FUZZY_LOGIC_EQUAL_H
