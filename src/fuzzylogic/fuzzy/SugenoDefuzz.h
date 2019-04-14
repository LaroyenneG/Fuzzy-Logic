#ifndef LOGIQUEFLOUE_SUGENODEFUZZ_H
#define LOGIQUEFLOUE_SUGENODEFUZZ_H

#include "NotBinaryShadowExpressionException.h"
#include "NotSugenoThenException.h"
#include "NotSugenoThenException.h"
#include "NotBinaryExpressionModelException.h"
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
            if (binaryExpressionModel == nullptr) {
                throw exception::NotBinaryExpressionModelException();
            }

            auto binaryShadowExpression = dynamic_cast<core::BinaryShadowExpression<T> *> (binaryExpressionModel->getOperator());
            if (binaryShadowExpression == nullptr) {
                throw exception::NotBinaryExpressionModelException();
            }

            auto sugenoThen = dynamic_cast<SugenoThen<T> *> (binaryShadowExpression->getTarget());
            if (sugenoThen == nullptr) {
                throw exception::NotSugenoThenException();
            }

            numerator += operand->evaluate();
            denominator += sugenoThen->getPremiseValue();
        }

        return (denominator != ZERO) ? numerator / denominator : ZERO;
    }
}

#endif //LOGIQUEFLOUE_SUGENODEFUZZ_H
