
#include "ThenTest.h"

void ThenTest::testThenMin() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.9);

    ThenMin<double> thenMin;

    CPPUNIT_ASSERT_EQUAL(0.5, thenMin.evaluate(&valueModelA, &valueModelB));
}

void ThenTest::testThenMult() {

    ValueModel valueModelA(0.4);
    ValueModel valueModdelB(0.6);

    ThenMult<double> thenMult;
    CPPUNIT_ASSERT_EQUAL(0.24, thenMult.evaluate(&valueModelA, &valueModdelB));
}