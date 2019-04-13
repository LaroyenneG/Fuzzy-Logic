#ifndef LOGIQUEFLOUE_EXPRESSIONFACTORY_H
#define LOGIQUEFLOUE_EXPRESSIONFACTORY_H

#include <set>
#include "Expression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"

namespace fuzzylogic::core {

    template<typename T>
    class ExpressionFactory {

    private:
        std::set<Expression<T> *> memory;

    public:
        virtual ~ExpressionFactory();

        Expression<T> *hold(Expression<T> *expression);

        Expression<T> *newUnary(UnaryExpression<T> *operand, Expression<T> *expression);

        Expression<T> *
        newBinary(BinaryExpression<T> *operand, Expression<T> *left, Expression<T> *right);
    };

    template<typename T>
    Expression<T> *ExpressionFactory<T>::hold(Expression<T> *expression) {

        memory.insert(expression);

        return expression;
    }

    template<typename T>
    Expression<T> *
    ExpressionFactory<T>::newUnary(UnaryExpression<T> *operand, Expression<T> *expression) {

        auto nExpression = new UnaryExpressionModel<T>(operand, expression);

        hold(nExpression);

        return nExpression;
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newBinary(BinaryExpression<T> *operand,
                                                   Expression<T> *left,
                                                   Expression<T> *right) {

        auto nExpression = new BinaryExpressionModel<T>(operand, left, right);

        hold(nExpression);

        return nExpression;
    }

    template<typename T>
    ExpressionFactory<T>::~ExpressionFactory() {

        for (auto expression : memory) {
            delete expression;
        }
    }
}


#endif //LOGIQUEFLOUE_EXPRESSIONFACTORY_H
