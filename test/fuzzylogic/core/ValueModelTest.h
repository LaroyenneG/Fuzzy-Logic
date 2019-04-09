#ifndef LOGIQUEFLOUE_VALUEMODELTEST_H
#define LOGIQUEFLOUE_VALUEMODELTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ValueModel.h"

using namespace core;

class ValueModelTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(ValueModelTest);
        CPPUNIT_TEST(testConstructor);
        CPPUNIT_TEST(testSetter);
    CPPUNIT_TEST_SUITE_END();

public:
    void testConstructor();

    void testSetter();
};


#endif //LOGIQUEFLOUE_VALUEMODELTEST_H
