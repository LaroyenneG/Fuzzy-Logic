#ifndef LOGIQUEFLOUE_ISSINGLETON_H
#define LOGIQUEFLOUE_ISSINGLETON_H

#include "Expression.h"
#include "Is.h"

namespace fuzzy {


    template<typename T>
    class IsSingleton : public Is<T> {
    private :
        T value;
    public:
        explicit IsSingleton(const T &_value);

        T evaluate(core::Expression<T> *expression) const override;

        const T &getValue() const;

        void setValue(const T &_value);
    };


    template<typename T>
    IsSingleton<T>::IsSingleton(const T &_value): value(_value) {}

    template<typename T>
    T IsSingleton<T>::evaluate(core::Expression<T> *expression) const {

        T evaluateValue = expression->evaluate();

        return (evaluateValue == value) ? core::Expression<T>::ONE : core::Expression<T>::ZERO;
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
