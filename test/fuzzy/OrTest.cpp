#include "OrTest.h"

void OrTest::testOrMax() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.7);

    OrMax<double> orMax;

    CPPUNIT_ASSERT_EQUAL(0.7, orMax.evaluate(&valueModelA, &valueModelB));
}
