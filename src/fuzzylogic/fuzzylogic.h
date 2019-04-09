#ifndef LOGIQUEFLOUE_FUZZYLOGIC_H
#define LOGIQUEFLOUE_FUZZYLOGIC_H

#include "NaryShadowExpression.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "NaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "UnaryExpressionModel.h"
#include "ValueModel.h"
#include "Expression.h"

namespace fuzzylogic {


    /****************************************** core *************************************************/

    /* Model */

    typedef core::ValueModel<double> ValueModel;

    typedef core::UnaryExpressionModel<double> UnaryExpressionModel;

    typedef core::BinaryExpressionModel<double> BinaryExpressionModel;

    typedef core::NaryExpressionModel<double> NaryExpressionModel;


    /* Shadow */

    typedef core::UnaryShadowExpression<double> UnaryShadowExpression;

    typedef core::BinaryShadowExpression<double> BinaryShadowExpression;

    typedef core::NaryShadowExpression<double> NaryShadowExpression;


    /***************************************** fuzzy **************************************************/


}


#endif //LOGIQUEFLOUE_FUZZYLOGIC_H
