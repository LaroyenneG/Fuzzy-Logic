
#ifndef LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H

#include "Expression.h"
#include "UnaryExpression.h"

namespace core {
    template<typename T>
    class UnaryExpressionModel : public Expression<T>, public UnaryExpression<T> {
    private:
        UnaryExpression<T> *m_operator;
        Expression<T> *operand;
    public:
        T evaluate() const override;

        T evaluate(const Expression<T> *o) const override;
    };

    template<typename T>
    T UnaryExpressionModel<T>::evaluate(const Expression<T> *o) const {
        if (m_operator != nullptr)
            return m_operator->evaluate(o);
        return 0;
    }

    template<typename T>
    T UnaryExpressionModel<T>::evaluate() const {
        if (operand != nullptr)
            return evaluate(operand);
        return 0;
    }
}

#endif //LOGIQUEFLOUE_UNARYEXPRESSIONMODEL_H
