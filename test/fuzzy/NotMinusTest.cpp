#include "NotMinusTest.h"
#include <cmath>


void NotMinusTest::testNotMinus() {

    ValueModel valueModelA(0.7);

    NotMinus<double> notMinus;

    double result = notMinus.evaluate(&valueModelA);
    double expected = 0.3;


    CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(result * 1000));
}