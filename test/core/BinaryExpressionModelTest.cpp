
#include "ValueModel.h"
#include "BinaryExpressionModelTest.h"


void BinaryExpressionModelTest::testOperandsNull() {

    BinaryExpressionModel<double> binaryExpressionModel(nullptr, nullptr, nullptr);

    try {
        binaryExpressionModel.evaluate();
        CPPUNIT_FAIL("missing exception");
    } catch (exception::OperandNullException &e) {
    }
}

void BinaryExpressionModelTest::testOperatorNull() {

    BinaryExpressionModel<double> binaryExpressionModel(nullptr, nullptr, nullptr);

    try {
        binaryExpressionModel.evaluate(nullptr, nullptr);
        CPPUNIT_FAIL("missing exception");
    } catch (exception::OperatorNullException &e) {
    }
}
