#include "NaryExpressionModelTest.h"

void NaryExpressionModelTest::testOperandsNull() {

    NaryExpressionModel<double> naryExpressionModel(nullptr);

    try {
        naryExpressionModel.evaluate();
        CPPUNIT_FAIL("missing exception");
    } catch (exception::OperandNullException &e) {
    }
}

void NaryExpressionModelTest::testOperatorNull() {

}
