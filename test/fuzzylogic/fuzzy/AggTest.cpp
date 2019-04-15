#include "AggTest.h"


void AggTest::testAggMax() {

    ValueModel<double> valueModelA(0.6);
    ValueModel<double> valueModelB(0.8);

    AggMax<double> aggMax;

    CPPUNIT_ASSERT_EQUAL(0.8, aggMax.evaluate(&valueModelA, &valueModelB));
}

void AggTest::testAggPlus() {

    ValueModel<double> valueModelA(0.2);
    ValueModel<double> valueModelB(0.3);

    AggPlus<double> aggPlus;

    CPPUNIT_ASSERT_EQUAL(0.44, aggPlus.evaluate(&valueModelA, &valueModelB));
}
