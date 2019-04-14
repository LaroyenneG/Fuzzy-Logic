#ifndef LOGIQUEFLOUE_FUZZYFACTORY_H
#define LOGIQUEFLOUE_FUZZYFACTORY_H

#include "NaryShadowExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "ExpressionFactory.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "Expression.h"

#include "SugenoConclusion.h"
#include "SugenoThen.h"
#include "SugenoDefuzz.h"
#include "MamdaniDefuzz.h"
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
        fuzzylogic::core::BinaryShadowExpression<T> *sAnd;
        fuzzylogic::core::BinaryShadowExpression<T> *sOr;
        fuzzylogic::core::BinaryShadowExpression<T> *sThen;
        fuzzylogic::core::BinaryShadowExpression<T> *sAgg;
        fuzzylogic::core::BinaryShadowExpression<T> *sMamdaniDefuzz;
        fuzzylogic::core::UnaryShadowExpression<T> *sNot;
        fuzzylogic::core::NaryShadowExpression<T> *sSugenoDefuzz;
        fuzzylogic::core::NaryShadowExpression<T> *sSugenoConclusion;

    protected:
        explicit FuzzyFactory(fuzzylogic::core::UnaryShadowExpression<T> *_sNot,
                              fuzzylogic::core::BinaryShadowExpression<T> *_sAnd,
                              fuzzylogic::core::BinaryShadowExpression<T> *_sOr,
                              fuzzylogic::core::BinaryShadowExpression<T> *_sThen,
                              fuzzylogic::core::BinaryShadowExpression<T> *_sAgg,
                              fuzzylogic::core::BinaryShadowExpression<T> *_sDefuzz,
                              fuzzylogic::core::NaryShadowExpression<T> *_sSugenoDefuzz,
                              fuzzylogic::core::NaryShadowExpression<T> *_sSugenoConclusion);

    public:
        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                              MamdaniDefuzz<T> *_mamdaniDefuzz, SugenoDefuzz<T> *_sugenoDefuzz,
                              SugenoConclusion<T> *_sugenoConclusion);

        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                              MamdaniDefuzz<T> *_mamdaniDefuzz);

        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, SugenoThen<T> *_then,
                              SugenoDefuzz<T> *_sugenoDefuzz,
                              SugenoConclusion<T> *_sugenoConclusion);

        ~FuzzyFactory() override;

        fuzzylogic::core::Expression<T> *
        newAnd(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::Expression<T> *
        newOr(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::Expression<T> *
        newThen(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::Expression<T> *
        newAgg(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right);

        fuzzylogic::core::Expression<T> *newNot(fuzzylogic::core::Expression<T> *operand);

        fuzzylogic::core::Expression<T> *newIs(Is<T> *shape, fuzzylogic::core::Expression<T> *operand);

        core::Expression<T> *
        newMamdaniDefuzz(core::Expression<T> *left, core::Expression<T> *right, const T &min, const T &max,
                         const T &step);

        void changeAnd(And<T> *_target);

        void changeOr(Or<T> *_target);

        void changeAgg(Agg<T> *_target);

        void changeThen(Then<T> *_target);

        void changeMamdaniDefuzz(MamdaniDefuzz<T> *_target);

        void changeNot(Not<T> *_target);

        void changeSugenoDefuzz(SugenoDefuzz<T> *_target);

        void changeSugenoConclusion(SugenoConclusion<T> *_target);
    };

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(fuzzylogic::core::UnaryShadowExpression<T> *_sNot,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_sAnd,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_sOr,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_sThen,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_sAgg,
                                  fuzzylogic::core::BinaryShadowExpression<T> *_sDefuzz,
                                  fuzzylogic::core::NaryShadowExpression<T> *_sSugenoDefuzz,
                                  fuzzylogic::core::NaryShadowExpression<T> *_sSugenoConclusion)
            : sAnd(_sAnd), sOr(_sOr), sThen(_sThen), sAgg(_sAgg), sMamdaniDefuzz(_sDefuzz), sNot(_sNot),
              sSugenoDefuzz(_sSugenoDefuzz), sSugenoConclusion(_sSugenoConclusion) {}

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                                  MamdaniDefuzz<T> *_mamdaniDefuzz, SugenoDefuzz<T> *_sugenoDefuzz,
                                  SugenoConclusion<T> *_sugenoConclusion)

            : FuzzyFactory(new core::UnaryShadowExpression<T>(_not),
                           new core::BinaryShadowExpression<T>(_and),
                           new core::BinaryShadowExpression<T>(_or),
                           new core::BinaryShadowExpression<T>(_then),
                           new core::BinaryShadowExpression<T>(_agg),
                           new core::BinaryShadowExpression<T>(_mamdaniDefuzz),
                           new core::NaryShadowExpression<T>(_sugenoDefuzz),
                           new core::NaryShadowExpression<T>(_sugenoConclusion)) {

    }

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                                  MamdaniDefuzz<T> *_mamdaniDefuzz)

            : FuzzyFactory(_not, _and, _or, _then, _agg, _mamdaniDefuzz, nullptr, nullptr) {
    }


    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, SugenoThen<T> *_then,
                                  SugenoDefuzz<T> *_sugenoDefuzz, SugenoConclusion<T> *_sugenoConclusion)

            :FuzzyFactory(_not, _and, _or, _then, nullptr, nullptr, _sugenoDefuzz, _sugenoConclusion) {

    }

    template<typename T>
    fuzzylogic::core::Expression<T> *
    FuzzyFactory<T>::newAnd(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {

        return fuzzylogic::core::ExpressionFactory<T>::newBinary(sAnd, left, right);
    }

    template<typename T>
    fuzzylogic::core::Expression<T> *
    FuzzyFactory<T>::newOr(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {

        return fuzzylogic::core::ExpressionFactory<T>::newBinary(sOr, left, right);
    }

    template<typename T>
    fuzzylogic::core::Expression<T> *
    FuzzyFactory<T>::newThen(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {

        return fuzzylogic::core::ExpressionFactory<T>::newBinary(sThen, left, right);
    }

    template<typename T>
    fuzzylogic::core::Expression<T> *
    FuzzyFactory<T>::newAgg(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) {

        return fuzzylogic::core::ExpressionFactory<T>::newBinary(sAgg, left, right);
    }

    template<typename T>
    fuzzylogic::core::Expression<T> *FuzzyFactory<T>::newNot(fuzzylogic::core::Expression<T> *operand) {

        return fuzzylogic::core::ExpressionFactory<T>::newUnary(sNot, operand);
    }

    template<typename T>
    fuzzylogic::core::Expression<T> *
    FuzzyFactory<T>::newIs(Is<T> *shape, fuzzylogic::core::Expression<T> *operand) {

        return fuzzylogic::core::ExpressionFactory<T>::newUnary(shape, operand);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newMamdaniDefuzz(core::Expression<T> *left, core::Expression<T> *right,
                                                           const T &min, const T &max, const T &step) {

        // In this class the sMamdaniDefuzz target can only contain a Mamdani instance

        auto *mamdaniDefuzz = dynamic_cast<MamdaniDefuzz<T> *>(sMamdaniDefuzz->getTarget());

        mamdaniDefuzz->setMin(min);
        mamdaniDefuzz->setMax(max);
        mamdaniDefuzz->setStep(step);

        return fuzzylogic::core::ExpressionFactory<T>::newBinary(sMamdaniDefuzz, left, right);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAnd(And<T> *_target) {
        sAnd->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeOr(Or<T> *_target) {
        sOr->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeAgg(Agg<T> *_target) {
        sAgg->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeThen(Then<T> *_target) {
        sThen->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeNot(Not<T> *_target) {
        sNot->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeMamdaniDefuzz(MamdaniDefuzz<T> *_target) {
        sMamdaniDefuzz->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeSugenoDefuzz(SugenoDefuzz<T> *_target) {
        sSugenoDefuzz->setTarget(_target);
    }

    template<typename T>
    void FuzzyFactory<T>::changeSugenoConclusion(SugenoConclusion<T> *_target) {
        sSugenoConclusion->setTarget(_target);
    }

    template<typename T>
    FuzzyFactory<T>::~FuzzyFactory() {

        delete sNot;
        delete sAgg;
        delete sThen;
        delete sMamdaniDefuzz;
        delete sOr;
        delete sAnd;
        delete sSugenoConclusion;
        delete sSugenoDefuzz;
    }
}
#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
