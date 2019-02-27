#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include <thread_db.h>
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {
    private:
        const BinaryExpression<T> *bOperator;
        const Expression<T> *left;
        const Expression<T> *right;
    public:
        explicit BinaryExpressionModel(const BinaryExpression<T> *_bOperator, const Expression<T> *_left,
                                       const Expression<T> *_right);

        explicit BinaryExpressionModel(const BinaryExpression<T> *_bOperator);

        T evaluate() const override;

        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;
    };

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(const BinaryExpression<T> *_bOperator, const Expression<T> *_left,
                                                    const Expression<T> *_right)
            : bOperator(_bOperator), left(_left), right(_right) {

    }

    template<typename T>
    BinaryExpressionModel<T>::BinaryExpressionModel(const BinaryExpression<T> *_bOperator)
            : bOperator(_bOperator), left(nullptr), right(nullptr) {

    }


    template<typename T>
    T BinaryExpressionModel<T>::evaluate() const {

        if (left == nullptr || right == nullptr) {
            throw std::exception();
        }

        return evaluate(left, right);
    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {

        if (bOperator == nullptr) {
            throw std::string("");
        }

        return bOperator->evaluate(left, right);
    }
}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
