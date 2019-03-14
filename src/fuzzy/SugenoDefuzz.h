#ifndef LOGIQUEFLOUE_SUGENODEFUZZ_H
#define LOGIQUEFLOUE_SUGENODEFUZZ_H

#include "NaryExpression.h"

namespace fuzzy {
    template<typename T>

    class SugenoDefuzz : core::NaryExpression<T> {

    public:
        T evaluate(const core::Expression<T> **oprands) const override;

    };

    template<typename T>

    T SugenoDefuzz<T>::evaluate(const core::Expression<T> **oprands) const {
        return 0;
    }
}

#endif //LOGIQUEFLOUE_SUGENODEFUZZ_H
