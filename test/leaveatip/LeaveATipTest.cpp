#include "LeaveATip.h"

#include "LeaveATipTest.h"


void LeaveATipTest::testLessonExample() {

    OPEN_FUZZY_SECURE_BLOCK {

        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.075, computeTip(3.0, 8.0), 0.001);

    } CLOSE_FUZZY_SECURE_BLOCK
}

void LeaveATipTest::testInterpreter() {

    OPEN_FUZZY_SECURE_BLOCK {

        static const std::vector<std::array<type, 2>> TEST_DATA = {{3.0, 8.0}}; // pair (service, food) a tester

        LeaveATip leaveATip;
        leaveATip.setMinTip(LEAVE_A_TIP_TEST_MIN_TIP);
        leaveATip.setMaxTip(LEAVE_A_TIP_TEST_MAX_TIP);

        for (auto data : TEST_DATA) {

            CPPUNIT_ASSERT_DOUBLES_EQUAL(computeTip(data[0], data[1]), leaveATip.evaluateTip(), 0.001);
        }

    } CLOSE_FUZZY_SECURE_BLOCK
}

type LeaveATipTest::computeTip(type service, type food) {

    //operators
    NotMinus opNot;
    AndMin opAnd;
    OrMax opOr;
    AggMax opAgg;
    ThenMin opThen;
    CogDefuzz opDefuzz;

    //fuzzy expression factory
    FuzzyFactory f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opDefuzz);


    //membership function
    IsTriangle poor(-5, 0, 5);
    IsTriangle good(0, 5, 10);
    IsTriangle excellent(5, 10, 15);

    IsTriangle cheap(0, 5, 10);
    IsTriangle average(10, 15, 20);
    IsTriangle generous(20, 25, 30);

    //values
    ValueModel vService(service);
    ValueModel vFoods(food);
    ValueModel vTips(0);

    Expression *r =
            f.newAgg(
                    f.newAgg(
                            f.newThen(
                                    f.newIs(&poor, &vService),
                                    f.newIs(&cheap, &vTips)
                            ),
                            f.newThen(
                                    f.newIs(&good, &vService),
                                    f.newIs(&average, &vTips)
                            )
                    ),
                    f.newThen(
                            f.newIs(&excellent, &vService),
                            f.newIs(&generous, &vTips)
                    )
            );

    //defuzzication
    Expression *system = f.newDefuzz(&vTips, r, LEAVE_A_TIP_TEST_MIN_TIP, LEAVE_A_TIP_TEST_MAX_TIP, 1.0);

    //apply input
    auto returnValue = system->evaluate();

    return returnValue;
}
