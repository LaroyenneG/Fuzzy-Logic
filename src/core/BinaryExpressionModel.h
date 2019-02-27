#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include <thread_db.h>
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {
    private:
        const BinaryExpression<T> *mOperator;
        const Expression<T> *left;
        const Expression<T> *right;
    public:
        explicit BinaryExpressionModel(const BinaryExpression<T> *_mOperator, const Expression<T> *_left,
                                       const Expression<T> *_right);

        explicit BinaryExpressionModel(const BinaryExpression<T> *_mOperator);

        T evaluate() const override;

        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;
    };

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(const BinaryExpression<T> *_mOperator, const Expression<T> *_left,
                                                    const Expression<T> *_right)
            : mOperator(_mOperator), left(_left), right(_right) {

    }

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(const BinaryExpression<T> *_mOperator)
            : mOperator(_mOperator), left(nullptr), right(nullptr) {

    }


    template<typename T>
    T BinaryExpressionModel<T>::evaluate() const {

        return mOperator->evaluate(left, right);
    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {

        return mOperator->evaluate(left, right);
    }
}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
