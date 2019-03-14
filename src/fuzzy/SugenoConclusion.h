#ifndef LOGIQUEFLOUE_SUGENOCONCLUSION_H
#define LOGIQUEFLOUE_SUGENOCONCLUSION_H

#include <vector>
#include "NaryExpression.h"

namespace fuzzy {
    template<typename T>

    class SugenoConclusion : core::NaryExpression<T> {

    private:
        std::vector<T> coef;

    public:
        T evaluate(const core::Expression<T> **operands) const override;
    };

    template<typename T>

    T SugenoConclusion<T>::evaluate(const core::Expression<T> **operands) const {
        return 0;
    }
}

#endif //LOGIQUEFLOUE_SUGENOCONCLUSION_H
