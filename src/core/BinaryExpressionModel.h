#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include "OperandNullException.h"
#include "OperatorNullException.h"
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {
    private:
        const BinaryExpression <T> *bOperator;
        const Expression <T> *left;
        const Expression <T> *right;
    public:
        explicit BinaryExpressionModel(const BinaryExpression <T> *_bOperator, const Expression <T> *_left,
                                       const Expression <T> *_right);

        T evaluate() const override;

        T evaluate(const Expression <T> *left, const Expression <T> *right) const override;

    };

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(const BinaryExpression <T> *_bOperator, const Expression <T> *_left,
                                                    const Expression <T> *_right)
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
    T BinaryExpressionModel<T>::evaluate(const Expression <T> *left, const Expression <T> *right) const {

        if (bOperator == nullptr) {
            throw exception::OperatorNullException();
        }

        return bOperator->evaluate(left, right);
    }
}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
