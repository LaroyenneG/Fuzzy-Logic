#ifndef LOGIQUEFLOUE_FUZZYLOGIC_H
#define LOGIQUEFLOUE_FUZZYLOGIC_H

#include "SugenoThen.h"
#include "SugenoConclusion.h"
#include "OrPlus.h"
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


    /***************************************** fuzzy **************************************************/

    /* Defuzz */

    typedef fuzzy::SugenoDefuzz<type> SugenoDefuzz;

    typedef fuzzy::CogDefuzz<type> CogDefuzz;

    typedef fuzzy::SugenoConclusion<type> SugenoConclusion;

    typedef fuzzy::SugenoThen<type> SugenoThen;


    /******************************************* is ****************************************************/

    typedef fuzzy::IsBell<type> IsBell;

    /******************************************** or ***************************************************/

    typedef fuzzy::OrPlus<type> OrPlus;


    /******************************************** factory ***********************************************/

    typedef fuzzy::FuzzyFactory<type> FuzzyFactory;

    /***************************************** interpreter ********************************************/

    typedef interpreter::FuzzyInterpreter<type> FuzzyInterpreter;
}


#endif //LOGIQUEFLOUE_FUZZYLOGIC_H
