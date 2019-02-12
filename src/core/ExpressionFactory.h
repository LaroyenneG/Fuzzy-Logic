#ifndef LOGIQUEFLOUE_EXPRESSIONFACTORY_H
#define LOGIQUEFLOUE_EXPRESSIONFACTORY_H

#include <vector>
#include <Expression.h>
#include <UnaryExpression.h>
#include <BinaryExpression.h>

namespace core {

    template<typename T>
    class ExpressionFactory {

    private:
        std::vector<const Expression<T> *> memory;

    public:
        ExpressionFactory() = default;

        ~ExpressionFactory() = default;

        Expression<T> *hold(const Expression<T> *expression);

        static Expression<T> *newUnary(const UnaryExpression<T> *operand, const Expression<T> *expression);

        static Expression<T> *
        newBinary(const BinaryExpression<T> *operand, const Expression<T> *left, const Expression<T> *right);
    };

    template<typename T>
    Expression<T> *ExpressionFactory<T>::hold(const Expression<T> *expression) {
        memory.push_back(expression);
        return expression;
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newUnary(const UnaryExpression<T> *operand, const Expression<T> *expression) {

        return nullptr;
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newBinary(const BinaryExpression<T> *operand, const Expression<T> *left,
                                                   const Expression<T> *right) {
        return nullptr;
    }
}


#endif //LOGIQUEFLOUE_EXPRESSIONFACTORY_H
