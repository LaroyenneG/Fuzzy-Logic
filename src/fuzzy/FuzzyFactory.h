#ifndef LOGIQUEFLOUE_FUZZYFACTORY_H
#define LOGIQUEFLOUE_FUZZYFACTORY_H

#include <UnaryExpression.h>
#include <BinaryExpression.h>
#include "ExpressionFactory.h"

using namespace core;

namespace fuzzy {

    template<typename T>
    class FuzzyFactory : public ExpressionFactory<T> {

    public:
        /*
        Expression<T> *newAnd(const Expression<T> *left, const Expression<T> *right);
        newOr(l: Expression, r:Expression): Expression
        newThen(l: Expression, r:Expression): Expression
        newAgg(l: Expression, r:Expression): Expression
        newDefuzz(l: Expression, r:Expression): Expression
        newNot(o:Expression):ExpressionModel
        newIs(s:Is, o:Expression);Expression
        changeAnd(o:And):void
        changeOr(o:Or):void
        changeThen(o: Then): void
         */
    };
}


#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
