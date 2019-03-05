#include "FuzzyFactoryTest.h"

void FuzzyFactoryTest::andFactoryTest() {

    ValueModel valueModelA(0.5);
    ValueModel valueModelB(0.7);
    ValueModel valueModelC(0.3);
    ValueModel valueModelD(0.4);

    AndMin<double> andMin;
    OrPlus<double> orPlus;
    ThenMin<double> thenMin;
    NotMinus<double> notMinus;
    AggMax<double> aggMax;

    FuzzyFactory<double> FuzzyFact(&notMinus, &andMin, &orPlus, &thenMin, &aggMax);

    //OrPlus<double> OrFuzzy =  FuzzyFact.newOr(&valueModelA,&valueModelB);
    // CPPUNIT_ASSERT_EQUAL(1.3,OrFuzzy.evaluate(&ValueModelA,&ValueModelB));
}
