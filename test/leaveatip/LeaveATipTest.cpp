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
    Value V_service(service);
    Value V_foods(food);
    Value V_tips(0);

    Expression *r =
            f.newAgg(
                    f.newAgg(
                            f.newThen(
                                    f.newIs(&poor, &V_service),
                                    f.newIs(&cheap, &V_tips)
                            ),
                            f.newThen(
                                    f.newIs(&good, &V_service),
                                    f.newIs(&average, &V_tips)
                            )
                    ),
                    f.newThen(
                            f.newIs(&excellent, &V_service),
                            f.newIs(&generous, &V_tips)
                    )
            );

    //defuzzication
    Expression *system = f.newDefuzz(&V_tips, r, 0, 25, 1);

    //apply input
    auto returnValue = system->evaluate();

    return returnValue;
}
