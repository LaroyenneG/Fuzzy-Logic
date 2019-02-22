#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "core/ValueModelTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "LogiqueFloue" << std::endl;
        exit(EXIT_FAILURE);
    }

    CPPUNIT_TEST_SUITE_REGISTRATION(ValueModelTest);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TextTestRunner runner;
    runner.addTest(registry.makeTest());
    runner.run();

    return EXIT_SUCCESS;
}