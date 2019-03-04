#ifndef LOGIQUEFLOUE_ORTEST_H
#define LOGIQUEFLOUE_ORTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "OrMax.h"
#include "OrPlus.h"
#include "ValueModel.h"

using namespace core;
using namespace fuzzy;

class OrTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(OrTest);
    CPPUNIT_TEST_SUITE_END();
public:
    void testOrMax();
};


#endif //LOGIQUEFLOUE_ORTEST_H
