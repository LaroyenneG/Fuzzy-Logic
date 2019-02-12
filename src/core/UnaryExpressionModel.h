

#ifndef LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryExpressionModel : public Expression<T> {
    private:
        UnaryExpression<T> m_operator;
        Expression<T> operand;
    public:
        T evaluate(void) const;

        T evaluate(Expression<T> o) const;
    };

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(Expression<T> o) const {
        if (m_operator != null)
            return m_operator.evaluate(o);
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(void) const {
        if (operand != null)
            return evaluate(operand);
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
