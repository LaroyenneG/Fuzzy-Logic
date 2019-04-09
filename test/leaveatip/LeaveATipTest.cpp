#include "LeaveATip.h"

#include "LeaveATipTest.h"


void LeaveATipTest::testLessonExample() {

    CPPUNIT_ASSERT_DOUBLES_EQUAL(4.075, computeTip(3.0, 8.0), 0.001);
}

void LeaveATipTest::testInterpreter() {

    static const std::vector<std::array<type, 2>> TEST_DATA = {{3.0, 8.0}}; // pair (service, food) a tester

    LeaveATip leaveATip;
    leaveATip.setMinTip(LEAVE_A_TIP_TEST_MIN_TIP);
    leaveATip.setMaxTip(LEAVE_A_TIP_TEST_MAX_TIP);

    for (auto data : TEST_DATA) {

        CPPUNIT_ASSERT_DOUBLES_EQUAL(computeTip(data[0], data[1]), leaveATip.evaluateTip(), 0.001);
    }
}

type LeaveATipTest::computeTip(type service, type food) {

    /* a completer  */

    return 0;
}
