#ifndef LOGIQUEFLOUE_FUZZYFACTORY_H
#define LOGIQUEFLOUE_FUZZYFACTORY_H

#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ExpressionFactory.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "Expression.h"

#include "And.h"
#include "Or.h"
#include "Then.h"
#include "Agg.h"
#include "Not.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class FuzzyFactory : public fuzzylogic::core::ExpressionFactory<T> {

    private:
        fuzzylogic::core::BinaryShadowExpression<T> *mAnd;
        fuzzylogic::core::BinaryShadowExpression<T> *mOr;
        fuzzylogic::core::BinaryShadowExpression<T> *mThen;
        fuzzylogic::core::BinaryShadowExpression<T> *mAgg;
        fuzzylogic::core::UnaryShadowExpression<T> *mNot;

    public:
        FuzzyFactory<T>(fuzzylogic::core::UnaryShadowExpression<T> *, fuzzylogic::core::BinaryShadowExpression<T> *,
                        fuzzylogic::core::BinaryShadowExpression<T> *, fuzzylogic::core::BinaryShadowExpression<T> *,
                        fuzzylogic::core::BinaryShadowExpression<T> *);

        fuzzylogic::core::BinaryExpression<T> *
        newAnd(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::BinaryExpression<T> *
        newOr(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::BinaryExpression<T> *
        newThen(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::BinaryExpression<T> *
        newAgg(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::UnaryExpression<T> *newNot(fuzzylogic::core::Expression<T> *operand);

        fuzzylogic::core::UnaryExpression<T> *newIs(Is<T> *s, fuzzylogic::core::Expression<T> *operand);

        void changeAnd(fuzzylogic::fuzzy::And<T> *_operator);

        void changeOr(fuzzylogic::fuzzy::Or<T> *_operator);

        void changeAgg(fuzzylogic::fuzzy::Agg<T> *_operator);

        void changeThen(fuzzylogic::fuzzy::Then<T> *_operator);

        void changeNot(fuzzylogic::fuzzy::Not<T> *_operator);

    };

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(fuzzylogic::core::UnaryShadowExpression<T> *_not,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_and,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_or,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_then,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_agg)
            :mAnd(_and), mOr(_or), mThen(_then), mAgg(_agg), mNot(_not) {}

    template<typename T>
    fuzzylogic::core::BinaryExpression<T> *
    FuzzyFactory<T>::newAnd(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {
        return fuzzylogic::core::ExpressionFactory<T>::newBinary(mAnd, left, right);
    }

    template<typename T>
    fuzzylogic::core::BinaryExpression<T> *
    FuzzyFactory<T>::newOr(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {
        return fuzzylogic::core::ExpressionFactory<T>::newBinary(mOr, left, right);
    }

    template<typename T>
    fuzzylogic::core::BinaryExpression<T> *
    FuzzyFactory<T>::newThen(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {
        return fuzzylogic::core::ExpressionFactory<T>::newBinary(mThen, left, right);
    }

    template<typename T>
    fuzzylogic::core::BinaryExpression<T> *
    FuzzyFactory<T>::newAgg(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {
        return fuzzylogic::core::ExpressionFactory<T>::newBinary(mAgg, left, right);
    }

    template<typename T>
    fuzzylogic::core::UnaryExpression<T> *FuzzyFactory<T>::newNot(fuzzylogic::core::Expression<T> *operand) {
        return fuzzylogic::core::ExpressionFactory<T>::newUnary(mNot, operand);
    }

    template<typename T>
    fuzzylogic::core::UnaryExpression<T> *FuzzyFactory<T>::newIs(Is<T> *s, fuzzylogic::core::Expression<T> *operand) {
        return fuzzylogic::core::ExpressionFactory<T>::newUnary(s, operand);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAnd(fuzzylogic::fuzzy::And<T> *_operator) {
        mAnd->setTarget(_operator);
    }

    template<typename T>
    void FuzzyFactory<T>::changeOr(fuzzylogic::fuzzy::Or<T> *_operator) {
        mOr->setTarget(_operator);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAgg(fuzzylogic::fuzzy::Agg<T> *_operator) {
        mAgg->setTarget(_operator);
    }

    template<typename T>
    void FuzzyFactory<T>::changeThen(fuzzylogic::fuzzy::Then<T> *_operator) {
        mThen->setTarget(_operator);
    }

    template<typename T>
    void FuzzyFactory<T>::changeNot(fuzzylogic::fuzzy::Not<T> *_operator) {
        mNot->setTarget(_operator);
    }

}
#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
