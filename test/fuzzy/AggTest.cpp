#include "AggTest.h"


void AggTest::testAggMax() {
    ValueModel valueModelA(0.6);
    ValueModel valueModelB(0.8);

    AggMax<double> aggMax;

    CPPUNIT_ASSERT_EQUAL(0.8, aggMax.evaluate(&valueModelA, &valueModelB));
}

void AggTest::testAggPlus() {
    ValueModel valueModelA(0.2);
    ValueModel valueModelB(0.3);

    AggPlus<double> aggPlus;

    CPPUNIT_ASSERT_EQUAL(0.5, aggPlus.evaluate(&valueModelA, &valueModelB));
}
