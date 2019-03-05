#ifndef LOGIQUEFLOUE_EXPRESSIONFACTORY_H
#define LOGIQUEFLOUE_EXPRESSIONFACTORY_H

#include <set>
#include "Expression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

namespace core {

    template<typename T>
    class ExpressionFactory {

    private:
        std::set<const Expression<T> *> memory;

    public:
        ExpressionFactory() = default;

        ~ExpressionFactory();

        Expression<T> *hold(const Expression<T> *expression);

        Expression<T> *newUnary(const UnaryExpression<T> *operand, const Expression<T> *expression);

        Expression<T> *
        newBinary(const BinaryExpression<T> *operand, const Expression<T> *left, const Expression<T> *right);
    };

    template<typename T>
    Expression<T> *ExpressionFactory<T>::hold(const Expression<T> *expression) {

        memory.push_back(expression);

        return expression;
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newUnary(const UnaryExpression<T> *operand, const Expression<T> *expression) {

        return hold(new UnaryExpression<T>(operand, expression));
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newBinary(const BinaryExpression<T> *operand, const Expression<T> *left,
                                                   const Expression<T> *right) {
        return hold(new BinaryExpression<T>(operand, left, right));
    }

    template<typename T>
    ExpressionFactory<T>::~ExpressionFactory() {

        for (auto expression : memory) {
            delete expression;
        }
    }
}


#endif //LOGIQUEFLOUE_EXPRESSIONFACTORY_H
