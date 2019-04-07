
#ifndef LOGIQUEFLOUE_FUZZYFACTORYTEST_H
#define LOGIQUEFLOUE_FUZZYFACTORYTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "FuzzyFactory.h"
#include "AndMin.h"
#include "AndMult.h"
#include "AndTest.h"
#include "ValueModel.h"
#include "OrMax.h"
#include "OrPlus.h"
#include "NotMinus.h"
#include "ThenMin.h"
#include "ThenMult.h"
#include "AggMax.h"

class FuzzyFactoryTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(FuzzyFactoryTest);
        CPPUNIT_TEST(FactoryTest);
    CPPUNIT_TEST_SUITE_END();
public:
    void FactoryTest();

};


#endif //LOGIQUEFLOUE_FUZZYFACTORYTEST_H
