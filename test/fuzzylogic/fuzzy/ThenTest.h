#ifndef LOGIQUEFLOUE_THENTEST_H
#define LOGIQUEFLOUE_THENTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ThenMin.h"
#include "ThenMult.h"
#include "ValueModel.h"
#include "SugenoThen.h"

using namespace fuzzylogic::core;
using namespace fuzzylogic::fuzzy;


class ThenTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(ThenTest);
        CPPUNIT_TEST(testThenMin);
        CPPUNIT_TEST(testThenMult);
        CPPUNIT_TEST(testSugenoThen);
    CPPUNIT_TEST_SUITE_END();
public:
    void testThenMin();

    void testThenMult();

    void testSugenoThen();

};


#endif //LOGIQUEFLOUE_THENTEST_H