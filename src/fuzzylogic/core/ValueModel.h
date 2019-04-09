#ifndef LOGIQUEFLOUE_VALUEMODEL_H
#define LOGIQUEFLOUE_VALUEMODEL_H

#include "Expression.h"

namespace core {

    template<typename T>
    class ValueModel : public Expression<T> {

    private:
        T value;
    public:
        explicit ValueModel(T _value);

        T evaluate() const override;

        void setValue(const T &_v);

        bool isValue() const;
    };

    template<typename T>
    ValueModel<T>::ValueModel(T _value) : value(_value) {
    }

    template<typename T>
    T ValueModel<T>::evaluate() const {
        return value;
    }

    template<typename T>
    void ValueModel<T>::setValue(const T &_v) {
        value = _v;
    }

    template<typename T>
    bool ValueModel<T>::isValue() const {
        return true;
    }
}

#endif //LOGIQUEFLOUE_VALUEMODEL_H