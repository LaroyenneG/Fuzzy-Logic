#include "FuzzyFactoryTest.h"
#include <cmath>

void FuzzyFactoryTest::factoryTest() {

    OPEN_FUZZY_SECURE_BLOCK {

        ValueModel valueModelA(0.5);
        ValueModel valueModelB(0.7);

        AndMin<double> andMin;
        OrPlus<double> orPlus;
        ThenMin<double> thenMin;
        NotMinus<double> notMinus;
        AggMax<double> aggMax;
        CogDefuzz<double> cogDefuzz;


        FuzzyFactory<double> fuzzyFact(&notMinus, &andMin, &orPlus, &thenMin, &aggMax, &cogDefuzz);

        auto *andFuzzy = fuzzyFact.newAnd(&valueModelA, &valueModelB);
        CPPUNIT_ASSERT_EQUAL(0.5, andFuzzy->evaluate());


        auto *orFuzzy = fuzzyFact.newOr(&valueModelA, &valueModelB);
        CPPUNIT_ASSERT_EQUAL(0.85, orFuzzy->evaluate());

        auto *thenFuzzy = fuzzyFact.newThen(&valueModelA, &valueModelB);
        CPPUNIT_ASSERT_EQUAL(0.5, thenFuzzy->evaluate());

        auto *aggFuzzy = fuzzyFact.newAgg(&valueModelA, &valueModelB);
        CPPUNIT_ASSERT_EQUAL(0.7, aggFuzzy->evaluate());

        auto *notFuzzy = fuzzyFact.newNot(&valueModelB);
        double result = notFuzzy->evaluate();
        double expected = 0.3;
        CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(result * 1000));


        AndMult<double> andMult;
        fuzzyFact.changeAnd(&andMult);
        auto *andMultFuzzy = fuzzyFact.newAnd(&valueModelA, &valueModelB);

        CPPUNIT_ASSERT_EQUAL(0.35, andMultFuzzy->evaluate());

    } CLOSE_FUZZY_SECURE_BLOCK;
}
