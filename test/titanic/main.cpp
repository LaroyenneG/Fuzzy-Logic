#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "PhysicObject2DTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : " << ((argc >= 1) ? argv[0] : "program") << std::endl;
        exit(EXIT_FAILURE);
    }

    CPPUNIT_TEST_SUITE_REGISTRATION(PhysicObject2DTest);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TextTestRunner runner;
    runner.addTest(registry.makeTest());

    runner.run();


    return EXIT_SUCCESS;
}