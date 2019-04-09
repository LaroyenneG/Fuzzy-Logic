#ifndef LOGIQUEFLOUE_LEAVEATIPTEST_H
#define LOGIQUEFLOUE_LEAVEATIP_H

#define LEAVE_A_TIP_INTERPRETER_FILE_PATH "../assets/leaveatip.fuzzy"
#define LEAVE_A_TIP_DEFAULT_VALUE 0.0

#include "fuzzylogic.h"


class LeaveATipTest {

private:
    fuzzylogic::FuzzyInterpreter fuzzyInterpreter;

    fuzzylogic::type service;
    fuzzylogic::type food;
    fuzzylogic::type minTip;
    fuzzylogic::type maxTip;

public:
    explicit LeaveATipTest(fuzzylogic::type _service, fuzzylogic::type _food, fuzzylogic::type _minTip,
                           fuzzylogic::type _maxTip);

    explicit LeaveATipTest();

    void setService(fuzzylogic::type _service);

    void setFood(fuzzylogic::type _food);

    void setMinTip(fuzzylogic::type _minTip);

    void setMaxTip(fuzzylogic::type _maxTip);

    fuzzylogic::type evaluateTip();
};


#endif //LOGIQUEFLOUE_LEAVEATIPTEST_H
