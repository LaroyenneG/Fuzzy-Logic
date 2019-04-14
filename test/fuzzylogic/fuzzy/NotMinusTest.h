#ifndef LOGIQUEFLOUE_NOTMINUSTEST_H
#define LOGIQUEFLOUE_NOTMINUSTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "Not.h"
#include "NotMinus1.h"
#include "ValueModel.h"

using namespace fuzzylogic::fuzzy;
using namespace fuzzylogic::core;

class NotMinusTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(NotMinusTest);
        CPPUNIT_TEST(testNotMinus);
    CPPUNIT_TEST_SUITE_END();

public:
    void testNotMinus();

};


#endif //LOGIQUEFLOUE_NOTMINUSTEST_H
