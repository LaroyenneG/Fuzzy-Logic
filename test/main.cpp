#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "./LogiqueFloue" << std::endl;
        exit(EXIT_FAILURE);
    }


    CppUnit::TextTestRunner runner;

    runner.run();

    return EXIT_SUCCESS;
}