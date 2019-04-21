#ifndef LOGIQUEFLOUE_FUZZYLOGIC_H
#define LOGIQUEFLOUE_FUZZYLOGIC_H

#include "SugenoThen.h"
#include "SugenoConclusion.h"
#include "OrPlus.h"
#include "AggMax.h"
#include "AggPlus.h"
#include "OrMax.h"
#include "NotMinus1.h"
#include "AndMin.h"
#include "AndMult.h"
#include "ThenMin.h"
#include "ThenMult.h"
#include "IsTriangle.h"
#include "IsRangeBell.h"
#include "IsGaussian.h"
#include "IsRampLeft.h"
#include "IsRampRight.h"
#include "IsShape.h"
#include "IsSigmoid.h"
#include "IsSingleton.h"
#include "isTrapezoid.h"
#include "Expression.h"
#include "IsBell.h"
#include "CogDefuzz.h"
#include "FuzzyFactory.h"
#include "SugenoDefuzz.h"
#include "FuzzyInterpreter.h"
#include "NaryShadowExpression.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "NaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "ExpressionFactory.h"
#include "UnaryExpressionModel.h"
#include "ValueModel.h"
#include "Expression.h"

namespace fuzzylogic {

    typedef double type;

    /****************************************** core *************************************************/

    /* Model */

    typedef core::ValueModel<type> ValueModel;

    typedef core::UnaryExpressionModel<type> UnaryExpressionModel;

    typedef core::BinaryExpressionModel<type> BinaryExpressionModel;

    typedef core::NaryExpressionModel<type> NaryExpressionModel;


    /* Shadow */

    typedef core::UnaryShadowExpression<type> UnaryShadowExpression;

    typedef core::BinaryShadowExpression<type> BinaryShadowExpression;

    typedef core::NaryShadowExpression<type> NaryShadowExpression;

    /* Expression */

    typedef core::Expression<type> Expression;


    /***************************************** fuzzy **************************************************/

    /* Defuzz */

    typedef fuzzy::SugenoDefuzz<type> SugenoDefuzz;

    typedef fuzzy::CogDefuzz<type> CogDefuzz;

    typedef fuzzy::SugenoConclusion<type> SugenoConclusion;

    typedef fuzzy::SugenoThen<type> SugenoThen;

    typedef fuzzy::Shape<type> Shape;


    /******************************************* is ****************************************************/

    typedef fuzzy::IsTriangle<type> IsTriangle;
    typedef fuzzy::IsBell<type> IsBell;
    typedef fuzzy::IsRangeBell<type> IsRangeBell;
    typedef fuzzy::IsGaussian<type> IsGaussian;
    typedef fuzzy::IsRampLeft<type> IsRampLeft;
    typedef fuzzy::IsRampRight<type> IsRampRight;
    typedef fuzzy::IsSingleton<type> IsSingleton;
    typedef fuzzy::IsSigmoid<type> IsSigmoid;
    typedef fuzzy::isTrapezoid<type> IsTrapezoid;


    /******************************************** agg ***************************************************/

    typedef fuzzy::AggPlus<type> AggPlus;
    typedef fuzzy::AggMax<type> AggMax;

    /******************************************** and ***************************************************/

    typedef fuzzy::AndMin<type> AndMin;
    typedef fuzzy::AndMult<type> AndMult;

    /******************************************** not ***************************************************/

    typedef fuzzy::NotMinus1<type> NotMinus;

    /******************************************** or ***************************************************/

    typedef fuzzy::OrPlus<type> OrPlus;
    typedef fuzzy::OrMax<type> OrMax;

    /******************************************** then ***************************************************/

    typedef fuzzy::ThenMin<type> ThenMin;
    typedef fuzzy::ThenMult<type> ThenMult;


    /******************************************** factory ***********************************************/

    typedef fuzzy::FuzzyFactory<type> FuzzyFactory;


    /***************************************** interpreter ********************************************/

    typedef interpreter::FuzzyInterpreter<type> FuzzyInterpreter;

    typedef interpreter::AbstractInterpreter<type> AbstractInterpreter;
}


#endif //LOGIQUEFLOUE_FUZZYLOGIC_H
