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
        core::BinaryShadowExpression<T> *sAnd;
        core::BinaryShadowExpression<T> *sOr;
        core::BinaryShadowExpression<T> *sThen;
        core::BinaryShadowExpression<T> *sAgg;
        core::BinaryShadowExpression<T> *sMamdaniDefuzz;
        core::UnaryShadowExpression<T> *sNot;
        core::NaryShadowExpression<T> *sSugenoDefuzz;

    protected:
        explicit FuzzyFactory(core::UnaryShadowExpression<T> *_sNot, core::BinaryShadowExpression<T> *_sAnd,
                              core::BinaryShadowExpression<T> *_sOr, core::BinaryShadowExpression<T> *_sThen,
                              core::BinaryShadowExpression<T> *_sAgg, core::BinaryShadowExpression<T> *_sDefuzz,
                              core::NaryShadowExpression<T> *_sSugenoDefuzz);

    public:
        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                              MamdaniDefuzz<T> *_mamdaniDefuzz, SugenoDefuzz<T> *_sugenoDefuzz);

        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                              MamdaniDefuzz<T> *_mamdaniDefuzz);

        explicit FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, SugenoThen<T> *_then,
                              SugenoDefuzz<T> *_sugenoDefuzz);

        FuzzyFactory(const FuzzyFactory<T> &factory);

        ~FuzzyFactory() override;

        core::Expression<T> *
        newAnd(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *
        newOr(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *
        newThen(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *
        newAgg(core::Expression<T> *left, core::Expression<T> *right);

        core::Expression<T> *newNot(core::Expression<T> *operand);

        core::Expression<T> *newIs(Is<T> *shape, core::Expression<T> *operand);

        core::Expression<T> *
        newMamdaniDefuzz(core::Expression<T> *left, core::Expression<T> *right, const T &min, const T &max,
                         const T &step);

        core::Expression<T> *
        newSugenoDefuzz(const std::vector<core::Expression<T> *> &operands);

        core::Expression<T> *
        newSugenoConclusion(SugenoConclusion<T> *_conclusion, const std::vector<core::Expression<T> *> &operands);

        void changeAnd(And<T> *_target);

        void changeOr(Or<T> *_target);

        void changeAgg(Agg<T> *_target);

        void changeThen(Then<T> *_target);

        void changeMamdaniDefuzz(MamdaniDefuzz<T> *_target);

        void changeNot(Not<T> *_target);

        void changeSugenoDefuzz(SugenoDefuzz<T> *_target);

    };

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(core::UnaryShadowExpression<T> *_sNot,
                                  core::BinaryShadowExpression<T> *_sAnd,
                                  core::BinaryShadowExpression<T> *_sOr,
                                  core::BinaryShadowExpression<T> *_sThen,
                                  core::BinaryShadowExpression<T> *_sAgg,
                                  core::BinaryShadowExpression<T> *_sDefuzz,
                                  core::NaryShadowExpression<T> *_sSugenoDefuzz)
            : sAnd(_sAnd), sOr(_sOr), sThen(_sThen), sAgg(_sAgg), sMamdaniDefuzz(_sDefuzz), sNot(_sNot),
              sSugenoDefuzz(_sSugenoDefuzz) {}

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                                  MamdaniDefuzz<T> *_mamdaniDefuzz, SugenoDefuzz<T> *_sugenoDefuzz)

            : FuzzyFactory(new core::UnaryShadowExpression<T>(_not),
                           new core::BinaryShadowExpression<T>(_and),
                           new core::BinaryShadowExpression<T>(_or),
                           new core::BinaryShadowExpression<T>(_then),
                           new core::BinaryShadowExpression<T>(_agg),
                           new core::BinaryShadowExpression<T>(_mamdaniDefuzz),
                           new core::NaryShadowExpression<T>(_sugenoDefuzz)) {

    }

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(const FuzzyFactory<T> &factory)
            : FuzzyFactory(factory.sNot->getTarget(),
                           factory.sAnd->getTarget(),
                           factory.sOr->getTarget(),
                           factory.sThen->getTarget(),
                           factory.sAgg->getTarget(),
                           factory.sMamdaniDefuzz->getTarget(),
                           factory.sSugenoDefuzz->getTarget()) {

    }

    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, Then<T> *_then, Agg<T> *_agg,
                                  MamdaniDefuzz<T> *_mamdaniDefuzz)

            : FuzzyFactory(_not, _and, _or, _then, _agg, _mamdaniDefuzz, nullptr) {
    }


    template<typename T>
    FuzzyFactory<T>::FuzzyFactory(Not<T> *_not, And<T> *_and, Or<T> *_or, SugenoThen<T> *_then,
                                  SugenoDefuzz<T> *_sugenoDefuzz)

            : FuzzyFactory(_not, _and, _or, _then, nullptr, nullptr, _sugenoDefuzz) {

    }

    template<typename T>
    core::Expression<T> *
    FuzzyFactory<T>::newAnd(core::Expression<T> *left, core::Expression<T> *right) {

        return core::ExpressionFactory<T>::newBinary(sAnd, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newOr(core::Expression<T> *left, core::Expression<T> *right) {

        return core::ExpressionFactory<T>::newBinary(sOr, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newThen(core::Expression<T> *left, core::Expression<T> *right) {

        return core::ExpressionFactory<T>::newBinary(sThen, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newAgg(core::Expression<T> *left, core::Expression<T> *right) {

        return core::ExpressionFactory<T>::newBinary(sAgg, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newNot(core::Expression<T> *operand) {

        return core::ExpressionFactory<T>::newUnary(sNot, operand);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newIs(Is<T> *shape, fuzzylogic::core::Expression<T> *operand) {

        return core::ExpressionFactory<T>::newUnary(shape, operand);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newMamdaniDefuzz(core::Expression<T> *left, core::Expression<T> *right,
                                                           const T &min, const T &max, const T &step) {

        // In this class the sMamdaniDefuzz target can only contain a Mamdani instance

        auto *mamdaniDefuzz = dynamic_cast<MamdaniDefuzz<T> *>(sMamdaniDefuzz->getTarget());

        mamdaniDefuzz->setMin(min);
        mamdaniDefuzz->setMax(max);
        mamdaniDefuzz->setStep(step);

        return core::ExpressionFactory<T>::newBinary(sMamdaniDefuzz, left, right);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newSugenoDefuzz(const std::vector<core::Expression<T> *> &operands) {

        return core::ExpressionFactory<T>::newNary(sSugenoDefuzz, operands);
    }

    template<typename T>
    core::Expression<T> *FuzzyFactory<T>::newSugenoConclusion(SugenoConclusion<T> *_conclusion,
                                                              const std::vector<core::Expression<T> *> &operands) {

        return core::ExpressionFactory<T>::newNary(_conclusion, operands);
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
    FuzzyFactory<T>::~FuzzyFactory() {

        delete sNot;
        delete sAgg;
        delete sThen;
        delete sMamdaniDefuzz;
        delete sOr;
        delete sAnd;
        delete sSugenoDefuzz;
    }
}
#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
