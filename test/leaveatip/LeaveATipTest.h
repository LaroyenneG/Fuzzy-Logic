#ifndef LOGIQUEFLOUE_LEAVEATIPTEST_H
#define LOGIQUEFLOUE_LEAVEATIPTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "fuzzylogic.h"

#define LEAVE_A_TIP_TEST_MIN_TIP 0.0
#define LEAVE_A_TIP_TEST_MAX_TIP 25.0

using namespace fuzzylogic;

class LeaveATipTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(LeaveATipTest);
        CPPUNIT_TEST(testLessonExample);
        CPPUNIT_TEST(testInterpreter);
    CPPUNIT_TEST_SUITE_END();

private:
    static type computeTip(type service, type food);

public:
    void testLessonExample();

    void testInterpreter();
};


#endif //LOGIQUEFLOUE_LEAVEATIPTEST_H
