#ifndef FUZZY_LOGIC_ISPARABLE_H
#define FUZZY_LOGIC_ISPARABLE_H

#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class IsParable : public Is<T> {
    private:
        T valueA;
        T valueB;

    public:
        explicit IsParable(const T &_A, const T &_B);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getValueA() const;

        const T &getValueB() const;

        void setValueA(const T &_A);

        void setValueB(const T &_B);

    };

    template<typename T>
    IsParable<T>::IsParable(const T &_A, const T &_B) : valueA(_A), valueB(_B) {
    }

    template<typename T>
    T IsParable<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        T value = expression->evaluate();
        return valueA * value * value + valueB;
    }

    template<typename T>
    const T &IsParable<T>::getValueA() const {
        return valueA;
    }

    template<typename T>
    const T &IsParable<T>::getValueB() const {
        return valueB;
    }

    template<typename T>
    void IsParable<T>::setValueA(const T &_A) {
        valueA = _A;
    }

    template<typename T>
    void IsParable<T>::setValueB(const T &_B) {
        valueB = _B;
    }
}
#endif //FUZZY_LOGIC_ISPARABLE_H
