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

namespace fuzzy {

    template<typename T>
    class FuzzyFactory : public core::ExpressionFactory<T> {
    private:

        core::BinaryShadowExpression<T> *mAnd;
        core::BinaryShadowExpression<T> *mOr;
        core::BinaryShadowExpression<T> *mThen;
        core::BinaryShadowExpression<T> *mAgg;
        core::UnaryShadowExpression<T> *mNot;
        // Defuzz<T> m_defuzz; TODO be carefull to Defuzz classeS

    public:
        // constructeur qui prend en paramettre des pointeurs
        FuzzyFactory<T>(core::UnaryShadowExpression<T> *, core::BinaryShadowExpression<T> *, core::BinaryShadowExpression<T> *, core::BinaryShadowExpression<T> *, core::BinaryShadowExpression<T> *);

        core::BinaryExpression<T> *newAnd(core::Expression<T> *left, core::Expression<T> *right);

        core::BinaryExpression<T> *newOr(core::Expression<T> *left, core::Expression<T> *right);

        core::BinaryExpression<T> *newThen(core::Expression<T> *left, core::Expression<T> *right);

        core::BinaryExpression<T> *newAgg(core::Expression<T> *left, core::Expression<T> *right);

        core::UnaryExpression<T> *newNot(core::Expression<T> *o);

        core::UnaryExpression<T> *newIs(Is<T> *s, core::Expression<T> *o);

        void changeAnd(fuzzy::And<T> *);

        void changeOr(fuzzy::Or<T> *);

        void changeAgg(fuzzy::Agg<T> *);

        void changeThen(fuzzy::Then<T> *);

        void changeNot(fuzzy::Not<T> *);

    };

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(core::UnaryShadowExpression<T> *_not, core::BinaryShadowExpression<T> *_and, core::BinaryShadowExpression<T> *_or, core::BinaryShadowExpression<T> *_then,
                                  core::BinaryShadowExpression<T> *_agg)
            :mAnd(_and), mOr(_or), mThen(_then), mAgg(_agg),mNot(_not) {}

    template<typename T>
    core::BinaryExpression<T> *FuzzyFactory<T>::newAnd(core::Expression<T> *left, core::Expression<T> *right) {
        return core::ExpressionFactory<T>::newBinary(mAnd, left, right);
    }

    template<typename T>
    core::BinaryExpression<T> *FuzzyFactory<T>::newOr(core::Expression<T> *left, core::Expression<T> *right) {
        return core::ExpressionFactory<T>::newBinary(mOr, left, right);
    }

    template<typename T>
    core::BinaryExpression<T> *FuzzyFactory<T>::newThen(core::Expression<T> *left, core::Expression<T> *right) {
        return core::ExpressionFactory<T>::newBinary(mThen, left, right);
    }

    template<typename T>
    core::BinaryExpression<T> *FuzzyFactory<T>::newAgg(core::Expression<T> *left, core::Expression<T> *right) {
        return core::ExpressionFactory<T>::newBinary(mAgg, left, right);
    }

    template<typename T>
    core::UnaryExpression<T> *FuzzyFactory<T>::newNot(core::Expression<T> *o) {
        return core::ExpressionFactory<T>::newUnary(mNot, o);
    }

    template<typename T>
    core::UnaryExpression<T> *FuzzyFactory<T>::newIs(Is<T> *s, core::Expression<T> *o) {
        return core::ExpressionFactory<T>::newUnary(s, o);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAnd(fuzzy::And<T> *o) {
        mAnd->setTarget(o);
    }

    template<typename T>
    void FuzzyFactory<T>::changeOr(fuzzy::Or<T> *o) {
        mOr->setTarget(o);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAgg(fuzzy::Agg<T> *o) {
        mAgg->setTarget(o);
    }

    template<typename T>
    void FuzzyFactory<T>::changeThen(fuzzy::Then<T> *o) {
        mThen->setTarget(o);
    }

    template<typename T>
    void FuzzyFactory<T>::changeNot(fuzzy::Not<T> *o) {
        mNot->setTarget(o);
    }

}
#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
