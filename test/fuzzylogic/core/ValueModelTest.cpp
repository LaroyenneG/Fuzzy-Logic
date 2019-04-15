#include "ValueModelTest.h"


void ValueModelTest::testConstructor() {

    ValueModel<double> valueModel(3.0);

    CPPUNIT_ASSERT_EQUAL(3.0, valueModel.evaluate());
}

void ValueModelTest::testSetter() {

    ValueModel<double> valueModel(5.0);

    CPPUNIT_ASSERT_EQUAL(5.0, valueModel.evaluate());

    valueModel.setValue(6.0);

    CPPUNIT_ASSERT_EQUAL(6.0, valueModel.evaluate());
}
