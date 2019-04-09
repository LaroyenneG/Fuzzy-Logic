#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "LeaveATipTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : " << ((argc >= 1) ? argv[0] : "program") << std::endl;
        exit(EXIT_FAILURE);
    }

    CPPUNIT_TEST_SUITE_REGISTRATION(LeaveATipTest);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TextTestRunner runner;
    runner.addTest(registry.makeTest());

    runner.run();

    return EXIT_SUCCESS;
}