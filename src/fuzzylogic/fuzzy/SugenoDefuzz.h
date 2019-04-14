#ifndef LOGIQUEFLOUE_SUGENODEFUZZ_H
#define LOGIQUEFLOUE_SUGENODEFUZZ_H

#include "BinaryShadowExpression.h"
#include "BinaryExpressionModel.h"
#include "NaryExpression.h"
#include "SugenoThen.h"

namespace fuzzylogic::fuzzy {
    template<typename T>

    class SugenoDefuzz : public fuzzylogic::core::NaryExpression<T> {

    public:
        T evaluate(const std::vector<core::Expression<T> *> &operands) const override;
    };

    template<typename T>

    T SugenoDefuzz<T>::evaluate(const std::vector<core::Expression<T> *> &operands) const {

        static const T ZERO(0);

        T numerator(0);
        T denominator(0);

        for (auto operand: operands) {

            auto binaryExpressionModel = dynamic_cast<core::BinaryExpressionModel<T> *> (operand);
            auto binaryShadowExpression = dynamic_cast<core::BinaryShadowExpression<T> *> (binaryExpressionModel->getOperator());
            auto sugenoThen = dynamic_cast<SugenoThen<T> *> (binaryShadowExpression->getTarget());

            numerator += operand->evaluate();
            denominator += sugenoThen->getPremiseValue();
        }

        return (denominator != ZERO) ? numerator / denominator : ZERO;
    }
}

#endif //LOGIQUEFLOUE_SUGENODEFUZZ_H
