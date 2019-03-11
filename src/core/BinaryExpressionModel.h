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

        Expression <T> *GetLeft();

        Expression <T> *GetRigft();

        BinaryExpression <T> *GetOperator();

        void SetLeft(Expression <T> *);

        void SetRight(Expression <T> *);

        void SetOperator(BinaryExpression <T> *);

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

    template<typename T>
    Expression <T> *BinaryExpressionModel<T>::GetLeft() {
        return left;
    }

    template<typename T>
    Expression <T> *BinaryExpressionModel<T>::GetRigft() {
        return right;
    }

    template<typename T>
    BinaryExpression <T> *BinaryExpressionModel<T>::GetOperator() {
        return bOperator;
    }

    template<typename T>
    void BinaryExpressionModel<T>::SetLeft(Expression <T> *_left) {
        left = _left;
    }

    template<typename T>
    void BinaryExpressionModel<T>::SetRight(Expression <T> *_right) {
        right = _right;
    }

    template<typename T>
    void BinaryExpressionModel<T>::SetOperator(BinaryExpression <T> *_bOperator) {
        bOperator = _bOperator;
    }


}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
