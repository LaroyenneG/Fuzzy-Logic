
#include "DefuzzTest.h"


void DefuzzTest::testCogDefuzz() {

    CogDefuzz<double> cogDefuzz(0.0, 10.0, 0.0001);

    ValueModel<double> valueModel(5.0);

    IsTriangle<double> isTriangle(0.0, 5.0, 10.0);

    UnaryExpressionModel expressionModel(&isTriangle, &valueModel);

    OPEN_FUZZY_SECURE_BLOCK {

        double result = cogDefuzz.evaluate(&valueModel, &expressionModel);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, result, 0.0001);

    } CLOSE_FUZZY_SECURE_BLOCK

    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, valueModel.evaluate(), 0.001);

    try {
        cogDefuzz.evaluate(&expressionModel, &valueModel);

        CPPUNIT_FAIL("no exception throw (ValueModel)");

    } catch (fuzzylogic::exception::FuzzyException &ignored) {}
}

void DefuzzTest::testSugenoDefuzz() {

    SugenoDefuzz<double> sugenoDefuzz;


}

void DefuzzTest::testSugenoConclusion() {

    SugenoConclusion<double> sugenoConclusion;


    std::vector<Expression<double> *> expressions;

    std::vector<double> coefficients;
    for (int i = 0; i < 1000; i++) {

        double c = 1.0 / (i + 1);

        coefficients.push_back(c);

        auto *valueModel = new ValueModel<double>();

        valueModel->setValue(i * 2.0);

        expressions.push_back(valueModel);
    }

    sugenoConclusion.setCoefficients(coefficients);


    double result = sugenoConclusion.evaluate(expressions);


    for (auto expression : expressions) {
        delete expression;
    }

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1985.02, result, 0.01);
}
