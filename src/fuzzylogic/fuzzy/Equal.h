#ifndef FUZZY_LOGIC_EQUAL_H
#define FUZZY_LOGIC_EQUAL_H

#include "Or.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class Equal : public Or<T> {
    public :
        T evaluate(fuzzylogic::core::Expression <T> *left, fuzzylogic::core::Expression <T> *right) const override;
    };

    template<typename T>
    T Equal<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        static const T ZERO(0);

        T l = left->evaluate();
        T r = right->evaluate();


        return (l == r) ? l : ZERO;
    }
}
#endif //FUZZY_LOGIC_EQUAL_H
