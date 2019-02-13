

#ifndef LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryExpressionModel : public Expression<T> {
    private:
        UnaryExpression<T> *m_operator;
        Expression<T> *operand;
    public:
        T evaluate(void) const override;

        T evaluate(Expression<T> *o) const override;
    };

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(Expression<T> *o) const {
        if (m_operator != nullptr)
            return m_operator.evaluate(o);
        return nullptr;
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(void) const {
        if (operand != nullptr)
            return evaluate(operand);
        return nullptr;
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
