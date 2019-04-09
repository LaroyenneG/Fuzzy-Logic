#include "LeaveATip.h"

LeaveATipTest::LeaveATipTest(fuzzylogic::type _service, fuzzylogic::type _food, fuzzylogic::type _minTip,
                             fuzzylogic::type _maxTip)
        : service(_service), food(_food), minTip(_minTip), maxTip(_maxTip) {

    std::fstream file(LEAVE_A_TIP_INTERPRETER_FILE_PATH);

    fuzzyInterpreter.executeFile(file);

    file.close();
}

LeaveATipTest::LeaveATipTest()
        : LeaveATipTest(LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE,
                        LEAVE_A_TIP_DEFAULT_VALUE) {

}

void LeaveATipTest::setService(fuzzylogic::type _service) {
    service = _service;
}

void LeaveATipTest::setFood(fuzzylogic::type _food) {
    food = _food;
}

void LeaveATipTest::setMinTip(fuzzylogic::type _minTip) {
    minTip = _minTip;
}

void LeaveATipTest::setMaxTip(fuzzylogic::type _maxTip) {
    maxTip = _maxTip;
}

fuzzylogic::type LeaveATipTest::evaluateTip() {
    return 0;
}
