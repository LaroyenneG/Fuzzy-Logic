#ifndef LOGIQUEFLOUE_FUZZYFACTORY_H
#define LOGIQUEFLOUE_FUZZYFACTORY_H

#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ExpressionFactory.h"
#include "Expression.h"
#include "Is.h"
#include "And.h"
#include "Or.h"
#include "Then.h"
#include "Is.h"
#include "Not.h"
#include "Agg.h"

namespace fuzzy {

    template<typename T>
    class FuzzyFactory : public core::ExpressionFactory<T> {
    private:
        Not<T> *mNot;
        And<T> *mAnd;
        Or<T> *mOr;
        Agg<T> *mAgg;
        // Defuzz<T> m_defuzz; TODO be carefull to Defuzz classeS
        Then<T> *mThen;
    public:
        // constructeur qui prend en paramettre des pointeurs
        FuzzyFactory<T>(Not<T> *, And<T> *, Or<T> *, Then<T> *, Agg<T> *);

        core::Expression<T> *newAnd(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *newOr(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *newThen(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *newAgg(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *newNot(core::Expression<T> *o);

        core::Expression<T> *newIs(Is<T> *s, core::Expression<T> *o);
    };

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(fuzzy::Not<T> *_not, fuzzy::And<T> *_and, fuzzy::Or<T> *_or, fuzzy::Then<T> *_then,
                                  fuzzy::Agg<T> *_agg)
            :mAnd(_and), mNot(_not), mOr(_or), mThen(_then), mAgg(_agg) {}

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newAnd(core::Expression<T> *left, core::Expression<T> *right) {
        return newBinary(mAnd, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newAgg(core::Expression<T> *left, core::Expression<T> *right) {
        return newBinary(mAgg, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newOr(core::Expression<T> *left, core::Expression<T> *right) {
        return newBinary(mOr, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newThen(core::Expression<T> *left, core::Expression<T> *right) {
        return newBinary(mThen, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newNot(core::Expression<T> *o) {
        return newUnary(mNot, o);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newIs(Is<T> *s, core::Expression<T> *o) {
        return newUnary(s, o);
    }
}


#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
