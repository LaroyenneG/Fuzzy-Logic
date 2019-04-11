#ifndef LOGIQUEFLOUE_SUGENODEFUZZ_H
#define LOGIQUEFLOUE_SUGENODEFUZZ_H

#include "NaryExpression.h"
#include "SugenoThen.h"

namespace fuzzylogic::fuzzy {
    template<typename T>

    class SugenoDefuzz : fuzzylogic::core::NaryExpression<T> {

    public:
        SugenoDefuzz() = default;

        T evaluate(const std::vector<core::Expression < T> *

        > &operands)
        const override;
    };

    template<typename T>

    T SugenoDefuzz<T>::evaluate(const std::vector<core::Expression < T> *

    > &operands) const {

    static const T ZERO(0);

    T numerator(0);
    T denominator(0);

    for (
    auto operand
    : operands) {

    auto *bem = dynamic_cast<core::BinaryExpressionModel <T> *> (operand);
    auto *bse = dynamic_cast<core::BinaryShadowExpression <T> *> (bem->getOperator());
    auto *sth = dynamic_cast<SugenoThen <T> *> (bse->getTarget());

    numerator += operand->

    evaluate();

    denominator += sth->

    getPremiseValue();
}

return (denominator != ZERO) ? numerator / denominator :
ZERO;
}
}

#endif //LOGIQUEFLOUE_SUGENODEFUZZ_H
