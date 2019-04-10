#ifndef LOGIQUEFLOUE_SUGENOCONCLUSION_H
#define LOGIQUEFLOUE_SUGENOCONCLUSION_H

#include <vector>
#include "NaryExpression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>

    class SugenoConclusion : fuzzylogic::core::NaryExpression<T> {

    private:
        std::vector<T> coefficients;

    public:
        T evaluate(const std::vector<fuzzylogic::core::Expression<T> *> &operands) const override;
    };

    template<typename T>

    T SugenoConclusion<T>::evaluate(const std::vector<fuzzylogic::core::Expression<T> *> &operands) const {
        return 0;
    }
}

#endif //LOGIQUEFLOUE_SUGENOCONCLUSION_H
