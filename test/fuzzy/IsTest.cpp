
#include "IsTest.h"
#include <cmath>

void IsTest::testIsTriangle() {

    IsTriangle<double> isTriangle(0.1, 0.6, 0.7);
    ValueModel<double> valueModelA(0.7);
    ValueModel<double> valueModelB(0.2);

    CPPUNIT_ASSERT_EQUAL(0.1, isTriangle.getMin());
    CPPUNIT_ASSERT_EQUAL(0.6, isTriangle.getMid());
    CPPUNIT_ASSERT_EQUAL(0.7, isTriangle.getMax());

    isTriangle.setMax(0.5);
    isTriangle.setMid(0.2);
    isTriangle.setMin(0.05);

    CPPUNIT_ASSERT_EQUAL(0.05, isTriangle.getMin());
    CPPUNIT_ASSERT_EQUAL(0.2, isTriangle.getMid());
    CPPUNIT_ASSERT_EQUAL(0.5, isTriangle.getMax());

    double evaluate = isTriangle.evaluate(&valueModelA);
    double expected = -0.444;

    double evaluate1 = isTriangle.evaluate(&valueModelB);
    double expected1 = 1.0;


    CPPUNIT_ASSERT_EQUAL(round(expected1 * 1000), round(evaluate1 * 1000));
    CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(evaluate * 1000));
}

void IsTest::testIsTrapezoid() {

    isTrapezoid<double> isTrapezoid(0.1, 0.7, 0.5, 0.5);
    ValueModel<double> valueModelA(0.7);
    ValueModel<double> valueModelB(1.2);
    ValueModel<double> valueModelC(0.3);

    CPPUNIT_ASSERT_EQUAL(0.1, isTrapezoid.getLowLeft());
    CPPUNIT_ASSERT_EQUAL(0.7, isTrapezoid.getLowRight());
    CPPUNIT_ASSERT_EQUAL(0.5, isTrapezoid.getHighLeft());
    CPPUNIT_ASSERT_EQUAL(0.5, isTrapezoid.getHighRight());

    isTrapezoid.setLowLeft(0.0);
    isTrapezoid.setLowRight(1.0);
    isTrapezoid.setHighLeft(0.6);
    isTrapezoid.setHighRight(0.7);

    CPPUNIT_ASSERT_EQUAL(0.0, isTrapezoid.getLowLeft());
    CPPUNIT_ASSERT_EQUAL(1.0, isTrapezoid.getLowRight());
    CPPUNIT_ASSERT_EQUAL(0.6, isTrapezoid.getHighLeft());
    CPPUNIT_ASSERT_EQUAL(0.7, isTrapezoid.getHighRight());

    CPPUNIT_ASSERT_EQUAL(1.0, isTrapezoid.evaluate(&valueModelA));
    CPPUNIT_ASSERT_EQUAL(0.0, isTrapezoid.evaluate(&valueModelB));

    double expected = 0.429;
    double evaluate = isTrapezoid.evaluate(&valueModelC);
    CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(evaluate * 1000));
}

void IsTest::testIsSingleton() {
    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.4);
    IsSingleton<double> isSingleton(0.5);

    CPPUNIT_ASSERT_EQUAL(0.5, isSingleton.getValue());
    isSingleton.setValue(0.4);
    CPPUNIT_ASSERT_EQUAL(0.4, isSingleton.getValue());

    CPPUNIT_ASSERT_EQUAL(1.0, isSingleton.evaluate(&valueModelB));
    CPPUNIT_ASSERT_EQUAL(0.0, isSingleton.evaluate(&valueModelA));

}

void IsTest::testIsRampRight() {
    IsRampRight<double> IsRampRight(0.1, 0.6, 0.7);
    ValueModel<double> valueModelA(0.01);
    ValueModel<double> valueModelB(0.4);

    CPPUNIT_ASSERT_EQUAL(0.1, IsRampRight.getMin());
    CPPUNIT_ASSERT_EQUAL(0.6, IsRampRight.getMid());
    CPPUNIT_ASSERT_EQUAL(0.7, IsRampRight.getMax());

    IsRampRight.setMax(0.5);
    IsRampRight.setMid(0.2);
    IsRampRight.setMin(0.05);

    CPPUNIT_ASSERT_EQUAL(0.05, IsRampRight.getMin());
    CPPUNIT_ASSERT_EQUAL(0.2, IsRampRight.getMid());
    CPPUNIT_ASSERT_EQUAL(0.5, IsRampRight.getMax());

    CPPUNIT_ASSERT_EQUAL(1.0, IsRampRight.evaluate(&valueModelB));
    CPPUNIT_ASSERT_EQUAL(0.0, IsRampRight.evaluate(&valueModelA));


}