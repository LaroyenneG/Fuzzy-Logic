
#ifndef LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H

#include <OperandNullException.h>
#include <OperatorNullException.h>
#include "Expression.h"
#include "UnaryExpression.h"
#include "OperatorNullException.h"

namespace core {
    template<typename T>
    class UnaryExpressionModel : public Expression<T>, public UnaryExpression<T> {

    private:
        const UnaryExpression<T> *uOperator;
        const Expression<T> *operand;

    public:
        T evaluate() const override;

        T evaluate(const Expression<T> *_operand) const override;
    };

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(const Expression<T> *_operand) const {

        if (uOperator == nullptr) {
            throw exception::OperatorNullException();
        }

        return uOperator->evaluate(_operand);
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate() const {

        if (operand == nullptr) {
            throw exception::OperandNullException();
        }

        return evaluate(operand);
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
