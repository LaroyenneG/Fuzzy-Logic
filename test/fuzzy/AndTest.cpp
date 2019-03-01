#include "AndTest.h"

void AndTest::testAndMin() {

    ValueModel valueModelA(0.5);
    ValueModel valueModelB(0.7);

    AndMin<double> andMin;

    CPPUNIT_ASSERT_EQUAL(0.5, andMin.evaluate(&valueModelA, &valueModelB));
}
