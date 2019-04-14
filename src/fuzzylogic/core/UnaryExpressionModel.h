
#ifndef LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H

#include <OperandNullException.h>
#include <OperatorNullException.h>
#include "Expression.h"
#include "UnaryExpression.h"
#include "OperatorNullException.h"

namespace fuzzylogic::core {
    template<typename T>
    class UnaryExpressionModel : public Expression<T>, public UnaryExpression<T> {

    private:
        UnaryExpression <T> *uOperator;
        Expression <T> *operand;

    public:
        explicit UnaryExpressionModel(UnaryExpression <T> *_uOperator, Expression <T> *_operand);

        T evaluate() const override;

        T evaluate(Expression <T> *_operand) const override;

        bool isValue() const;

        const Expression <T> *getOperator() const;

        Expression <T> *getOperator();
    };

    template<typename T>
    UnaryExpressionModel<T>::UnaryExpressionModel(UnaryExpression <T> *_uOperator, Expression <T> *_operand)
            : uOperator(_uOperator), operand(_operand) {
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(Expression <T> *_operand) const {

        if (uOperator == nullptr) {
            throw fuzzylogic::exception::OperatorNullException();
        }

        return uOperator->evaluate(_operand);
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate() const {

        if (operand == nullptr) {
            throw fuzzylogic::exception::OperandNullException();
        }

        return evaluate(operand);
    }

    template<typename T>
    bool UnaryExpressionModel<T>::isValue() const {
        return false;
    }

    template<typename T>
    const Expression <T> *UnaryExpressionModel<T>::getOperator() const {

        return uOperator;
    }

    template<typename T>
    Expression <T> *UnaryExpressionModel<T>::getOperator() {

        return uOperator;
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
