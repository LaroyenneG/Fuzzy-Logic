#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include "OperandNullException.h"
#include "OperatorNullException.h"
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {
    private:
        BinaryExpression <T> *bOperator;
        Expression <T> *left;
        Expression <T> *right;
    public:
        explicit BinaryExpressionModel(BinaryExpression <T> *_bOperator, Expression <T> *_left,
                                       Expression <T> *_right);

        T evaluate() const override;

        T evaluate(Expression <T> *left, Expression <T> *right) const override;

        bool isValue() const override;
    };

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(BinaryExpression <T> *_bOperator, Expression <T> *_left,
                                                    Expression <T> *_right)
            : bOperator(_bOperator), left(_left), right(_right) {

    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate() const {

        if (left == nullptr || right == nullptr) {
            throw exception::OperandNullException();
        }

        return evaluate(left, right);
    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(Expression <T> *left, Expression <T> *right) const {

        if (bOperator == nullptr) {
            throw exception::OperatorNullException();
        }

        return bOperator->evaluate(left, right);
    }

    template<typename T>
    bool BinaryExpressionModel<T>::isValue() const {
        return false;
    }
}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
