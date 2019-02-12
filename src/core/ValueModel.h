#ifndef LOGIQUEFLOUE_VALUEMODEL_H
#define LOGIQUEFLOUE_VALUEMODEL_H

#include "Expression.h"

namespace core {
    template<typename T>
    class ValueModel : public Expression<T> {
    private:
        T value;
    public:
        T evaluate(void) const;

        void setValue(T _v);

    };

    template<typename T>
    T ValueModel<T>::evaluate(void) const {
        return nullptr;
    }

    template<typename T>
    void ValueModel<T>::setValue(T _v) {
        value = _v;
    }
}

#endif //LOGIQUEFLOUE_VALUEMODEL_H
