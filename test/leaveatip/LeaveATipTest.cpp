#include "LeaveATip.h"

#include "LeaveATipTest.h"


void LeaveATipTest::testLessonExample() {

    OPEN_FUZZY_SECURE_BLOCK {

        CPPUNIT_ASSERT_DOUBLES_EQUAL(16.716, computeTipWithCog(3.0, 8.0), 0.001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(10.597, computeTipWithSugeno(3.0, 8.0), 0.001);

    } CLOSE_FUZZY_SECURE_BLOCK
}

void LeaveATipTest::testInterpreter() {

    OPEN_FUZZY_SECURE_BLOCK {

        static const std::vector<std::array<type, 2>> TEST_DATA = {{3.0, 8.0},
                                                                   {5.0, 7.0},
                                                                   {8.0, 6.0}}; // pair (service, food) to test

        LeaveATip leaveATipCog(LEAVE_A_TIP_INTERPRETER_M_COG_FILE_PATH);

        for (auto data : TEST_DATA) {

            leaveATipCog.setService(data[0]);
            leaveATipCog.setFood(data[1]);

            CPPUNIT_ASSERT_DOUBLES_EQUAL(computeTipWithCog(data[0], data[1]), leaveATipCog.evaluateTip(), 0.001);
        }

    } CLOSE_FUZZY_SECURE_BLOCK
}

type LeaveATipTest::computeTipWithCog(type service, type food) {

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
    IsRampRight rancid(0, 5, 5);
    IsRampLeft delicious(5, 10, 10);

    IsRangeBell poor(1, 1, 0, 0, 5);
    IsBell good(1.2, 3.2, 5);
    IsRangeBell excellent(1, 1, 10, 5, 10);

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
                                    f.newOr(f.newIs(&poor, &vService), f.newIs(&rancid, &vFoods)),
                                    f.newIs(&cheap, &vTips)
                            ),
                            f.newThen(
                                    f.newIs(&good, &vService),
                                    f.newIs(&average, &vTips)
                            )
                    ),
                    f.newThen(
                            f.newOr(f.newIs(&excellent, &vService), f.newIs(&delicious, &vFoods)),
                            f.newIs(&generous, &vTips)
                    )
            );

    //defuzzication
    Expression *system = f.newMamdaniDefuzz(&vTips, r, LEAVE_A_TIP_TEST_MIN_TIP, LEAVE_A_TIP_TEST_MAX_TIP, 1.0);

    //apply input
    auto returnValue = system->evaluate();

    return returnValue;
}

type LeaveATipTest::computeTipWithSugeno(type service, type food) {

    std::vector<Expression *> rules;
    std::vector<Expression *> conclusionServiceFood;
    std::vector<Expression *> conlusionService;
    std::vector<type> coeffs{{1.0, 1.0}};

    //operators
    NotMinus opNot;
    AndMin opAnd;
    OrMax opOr;
    SugenoThen opThen;
    SugenoDefuzz opDefuzz;
    SugenoConclusion opConclusion(coeffs);


    //fuzzy factory expression
    FuzzyFactory f(&opNot, &opAnd, &opOr, &opThen, &opDefuzz, &opConclusion);

    //membership function
    IsRampRight rancid(0, 5, 5);
    IsRampLeft delicious(5, 10, 10);

    IsRangeBell poor(1, 1, 0, 0, 5);
    IsBell good(1.2, 3.2, 5);
    IsRangeBell excellent(1, 1, 10, 5, 10);

    IsTriangle cheap(0, 5, 10);
    IsTriangle average(10, 15, 20);
    IsTriangle generous(20, 25, 30);

    //values
    ValueModel vService(service);
    ValueModel vFoods(food);

    conclusionServiceFood.push_back(&vService);
    conclusionServiceFood.push_back(&vFoods);

    conlusionService.push_back(&vService);

    Expression *r1 =
            f.newThen(
                    f.newOr(
                            f.newIs(&excellent, &vService),
                            f.newIs(&rancid, &vFoods)
                    ),
                    f.newSugenoConclusion(conclusionServiceFood)
            );

    rules.push_back(r1);

    Expression *r2 =
            f.newThen(
                    f.newIs(&good, &vService),
                    f.newSugenoConclusion(conlusionService)
            );

    rules.push_back(r2);

    Expression *r3 =
            f.newThen(
                    f.newOr(
                            f.newIs(&excellent, &vService),
                            f.newIs(&delicious, &vFoods)
                    ),
                    f.newSugenoConclusion(conclusionServiceFood)
            );

    rules.push_back(r3);

    //defuzzification
    Expression *system = f.newSugenoDefuzz(rules);

    return system->evaluate();
}
