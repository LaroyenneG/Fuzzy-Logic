#ifndef LOGIQUEFLOUE_EXPRESSIONFACTORY_H
#define LOGIQUEFLOUE_EXPRESSIONFACTORY_H

#include <set>
#include "Expression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "NaryExpressionModel.h"

namespace fuzzylogic::core {

    template<typename T>
    class ExpressionFactory {

    private:
        std::set<Expression<T> *> memory;

    public:
        virtual ~ExpressionFactory();

        Expression<T> *hold(Expression<T> *expression);

        Expression<T> *newUnary(UnaryExpression<T> *uOperator, Expression<T> *expression);

        Expression<T> *
        newBinary(BinaryExpression<T> *bOperator, Expression<T> *left, Expression<T> *right);

        Expression<T> *newNary(NaryExpression<T> *nOperator, const std::vector<Expression<T> *> &operands);
    };

    template<typename T>
    Expression<T> *ExpressionFactory<T>::hold(Expression<T> *expression) {

        memory.insert(expression);

        return expression;
    }

    template<typename T>
    Expression<T> *
    ExpressionFactory<T>::newUnary(UnaryExpression<T> *uOperator, Expression<T> *expression) {

        auto nExpression = new UnaryExpressionModel<T>(uOperator, expression);

        hold(nExpression);

        return nExpression;
    }

    template<typename T>
    Expression<T> *ExpressionFactory<T>::newBinary(BinaryExpression<T> *bOperator,
                                                   Expression<T> *left,
                                                   Expression<T> *right) {

        auto nExpression = new BinaryExpressionModel<T>(bOperator, left, right);

        hold(nExpression);

        return nExpression;
    }

    template<typename T>
    Expression<T> *
    ExpressionFactory<T>::newNary(NaryExpression<T> *nOperator, const std::vector<Expression<T> *> &operands) {

        auto nExpression = new NaryExpressionModel<T>(nOperator, operands);

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
