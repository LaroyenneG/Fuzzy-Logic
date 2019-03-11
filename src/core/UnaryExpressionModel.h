
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
        explicit UnaryExpressionModel(const UnaryExpression<T> *_uOperator, const Expression<T> *_operand);

        T evaluate() const override;

        T evaluate(const Expression<T> *_operand) const override;

        Expression<T> *GetuOperator();

        Expression<T> *GetOperand();

        void SetuOperator(Expression<T> *);

        void SetOperand(Expression<T> *);

    };

    template<typename T>
    UnaryExpressionModel<T>::UnaryExpressionModel(const UnaryExpression<T> *_uOperator, const Expression<T> *_operand)
            : uOperator(_uOperator), operand(_operand) {
    }

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

    template<typename T>
    Expression<T> *UnaryExpressionModel<T>::GetuOperator() {
        return uOperator;
    }

    template<typename T>
    Expression<T> *UnaryExpressionModel<T>::GetOperand() {
        return operand;
    }

    template<typename T>
    void UnaryExpressionModel<T>::SetuOperator(Expression<T> *_uOperator) {
        uOperator = _uOperator;
    }

    template<typename T>
    void UnaryExpressionModel<T>::SetOperand(Expression<T> *_operand) {
        operand = _operand;
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
