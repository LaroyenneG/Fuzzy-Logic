#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <BinaryExpressionModel.h>
#include <FuzzyFactory.h>
#include <BinaryShadowExpression.h>
#include <UnaryExpressionModel.h>
#include <ValueModel.h>

using namespace fuzzy;

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "LogiqueFloue" << std::endl;
        exit(EXIT_FAILURE);
    }

    FuzzyFactory<float> fuzzyFactory;

    BinaryExpressionModel<float> binaryExpressionModel;

    BinaryShadowExpression<float> binaryShadowExpression;

    UnaryExpressionModel<float> expressionModel;

    ValueModel<float> model(0.0);

    CppUnit::TextTestRunner runner;

    runner.run();

    return EXIT_SUCCESS;
}