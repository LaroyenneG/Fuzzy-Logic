
#include <ValueModel.h>
#include "BinaryExpressionModelTest.h"

void BinaryExpressionModelTest::testOrMax() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.7);

    OrMax<double> orMax;

    CPPUNIT_ASSERT_EQUAL(0.7, orMax.evaluate(&valueModelA, &valueModelB));
}

void BinaryExpressionModelTest::testAndMin() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.7);

    AndMin<double> andMin;

    CPPUNIT_ASSERT_EQUAL(0.5, andMin.evaluate(&valueModelA, &valueModelB));
}