
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
#include "NotMinus1.h"
#include "ThenMin.h"
#include "ThenMult.h"
#include "AggMax.h"
#include "CogDefuzz.h"

class FuzzyFactoryTest : public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(FuzzyFactoryTest);
        CPPUNIT_TEST(factoryTest);
    CPPUNIT_TEST_SUITE_END();
public:
    void factoryTest();

};


#endif //LOGIQUEFLOUE_FUZZYFACTORYTEST_H
