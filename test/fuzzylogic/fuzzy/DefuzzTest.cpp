
#include "NotMinus.h"
#include "UnaryExpressionModel.h"
#include "DefuzzTest.h"

void DefuzzTest::testCogDefuzz() {

    CogDefuzz<double> cogDefuzz(0.0, 10.0, 1.0);

    ValueModel<double> valueModel(0.0);

    NotMinus<double> notMinus;

    UnaryExpressionModel expressionModel(&notMinus, &valueModel);

    OPEN_FUZZY_SECURE_BLOCK {

        double result = cogDefuzz.evaluate(&expressionModel, &valueModel);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.5, result, 0.005);

    } CLOSE_FUZZY_SECURE_BLOCK


    try {
        cogDefuzz.evaluate(&valueModel, &expressionModel);

        CPPUNIT_FAIL("no exception throw (ValueModel)");

    } catch (exception::FuzzyException &ignored) {}
}
