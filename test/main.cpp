#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <BinaryShadowExpression.h>

#include "core/ValueModelTest.h"
#include "core/BinaryExpressionModelTest.h"
#include "core/UnaryExpressionModelTest.h"
#include "core/NaryExpressionModelTest.h"
#include "core/NaryShadowExpressionTest.h"
#include "core/BinaryShadowExpressionTest.h"
#include "core/UnaryShadowExpressionTest.h"

#include "fuzzy/ShapeTest.h"
#include "fuzzy/FuzzyFactoryTest.h"
#include "fuzzy/OrTest.h"
#include "fuzzy/NotMinusTest.h"
#include "fuzzy/ThenTest.h"
#include "fuzzy/IsTest.h"
#include "fuzzy/AggTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "LogiqueFloue" << std::endl;
        exit(EXIT_FAILURE);
    }

    CPPUNIT_TEST_SUITE_REGISTRATION(ValueModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(BinaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(UnaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(NaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(NaryShadowExpressionTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(BinaryShadowExpressionTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(UnaryShadowExpressionTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(FuzzyFactoryTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(OrTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(AndTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(AggTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(NotMinusTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(ThenTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(ShapeTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(IsTest);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TextTestRunner runner;
    runner.addTest(registry.makeTest());

    runner.run();

    return EXIT_SUCCESS;
}