//
// Created by rabougris on 2/12/19.
//

#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include <thread_db.h>
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {
    private:
        BinaryExpression<T> *m_operator;
        const Expression<T> *left;
        const Expression<T> *right;
    public:
        T evaluate() const override;

        T evaluate(const Expression<T> *left, const Expression<T> *right) const override;
    };


    template<typename T>
    T BinaryExpressionModel<T>::evaluate() const {

        if (left != nullptr && right != nullptr) {
            return evaluate(left, right);
        }

        return 0;
    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(const Expression<T> *left, const Expression<T> *right) const {

        if (m_operator != nullptr) {
            return m_operator->evaluate(left, right);
        }

        return 0;
    }

}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
