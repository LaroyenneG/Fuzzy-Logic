#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "core/ValueModelTest.h"
#include "core/BinaryExpressionModelTest.h"
#include "core/UnaryExpressionModelTest.h"
#include "core/NaryExpressionModelTest.h"
#include "fuzzy/FuzzyFactoryTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "LogiqueFloue" << std::endl;
        exit(EXIT_FAILURE);
    }

    CPPUNIT_TEST_SUITE_REGISTRATION(ValueModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(BinaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(UnaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(NaryExpressionModelTest);
    CPPUNIT_TEST_SUITE_REGISTRATION(FuzzyFactoryTest);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TextTestRunner runner;
    runner.addTest(registry.makeTest());
    runner.run();

    return EXIT_SUCCESS;
}