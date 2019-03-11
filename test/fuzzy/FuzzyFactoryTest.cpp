#include "FuzzyFactoryTest.h"

void FuzzyFactoryTest::andFactoryTest() {

    ValueModel valueModelA(0.5);
    ValueModel valueModelB(0.7);


    AndMin<double> andMin;
    OrPlus<double> orPlus;
    ThenMin<double> thenMin;
    NotMinus<double> notMinus;
    AggMax<double> aggMax;

    UnaryShadowExpression<double> shadowNot(&notMinus);
    BinaryShadowExpression<double> shadowAnd(&andMin);
    BinaryShadowExpression<double> shadowOr(&orPlus);
    BinaryShadowExpression<double> shadowThen(&thenMin);
    BinaryShadowExpression<double> shadowAgg(&aggMax);



    FuzzyFactory<double> fuzzyFact(&shadowNot, &shadowAnd, &shadowOr, &shadowThen, &shadowAgg);

    AndMin<double> *andFuzzy = (AndMin<double> *)fuzzyFact.newAnd(&valueModelA,&valueModelB);
    CPPUNIT_ASSERT_EQUAL(0.5,andFuzzy->evaluate(&valueModelA,&valueModelB));


    OrPlus<double> *orFuzzy = (OrPlus<double> *)fuzzyFact.newOr(&valueModelA,&valueModelB);
    CPPUNIT_ASSERT_EQUAL(1.2,orFuzzy->evaluate(&valueModelA,&valueModelB));

    ThenMin<double> *thenFuzzy = (ThenMin<double>*)fuzzyFact.newThen(&valueModelA,&valueModelB);
    CPPUNIT_ASSERT_EQUAL(0.5,thenFuzzy->evaluate(&valueModelA,&valueModelB));

    



}
