#ifndef LOGIQUEFLOUE_THENTEST_H
#define LOGIQUEFLOUE_THENTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ThenMin.h"
#include "ThenMult.h"
#include "ValueModel.h"

using namespace core;
using namespace fuzzy;


class ThenTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(ThenTest);
        CPPUNIT_TEST(testThenMin);
        CPPUNIT_TEST(testThenMult);
    CPPUNIT_TEST_SUITE_END();
public:
    void testThenMin();

    void testThenMult();

};


#endif //LOGIQUEFLOUE_THENTEST_H