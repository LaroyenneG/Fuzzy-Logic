#ifndef LOGIQUEFLOUE_SUGENODEFUZZ_H
#define LOGIQUEFLOUE_SUGENODEFUZZ_H

#include "NaryExpression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>

    class SugenoDefuzz : fuzzylogic::core::NaryExpression<T> {

    public:
        T evaluate(const fuzzylogic::core::Expression<T> **oprands) const override;
    };

    template<typename T>

    T SugenoDefuzz<T>::evaluate(const fuzzylogic::core::Expression<T> **oprands) const {
        return 0;
    }
}

#endif //LOGIQUEFLOUE_SUGENODEFUZZ_H
