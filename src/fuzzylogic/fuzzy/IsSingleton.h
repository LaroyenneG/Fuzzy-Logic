#ifndef LOGIQUEFLOUE_ISSINGLETON_H
#define LOGIQUEFLOUE_ISSINGLETON_H

#include "Expression.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {


    template<typename T>
    class IsSingleton : public Is<T> {
    private :
        T value;
    public:
        explicit IsSingleton(const T &_value);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getValue() const;

        void setValue(const T &_value);
    };


    template<typename T>
    IsSingleton<T>::IsSingleton(const T &_value): value(_value) {}

    template<typename T>
    T IsSingleton<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        static const T ONE(1);
        static const T ZERO(0);

        return (expression->evaluate() == value) ? ONE : ZERO;
    }

    template<typename T>
    const T &IsSingleton<T>::getValue() const {
        return value;
    }

    template<typename T>
    void IsSingleton<T>::setValue(const T &_value) {
        value = _value;
    }
}

#endif //LOGIQUEFLOUE_ISSINGLETON_H
