#include "LeaveATip.h"

LeaveATip::LeaveATip(fuzzylogic::type _service, fuzzylogic::type _food, fuzzylogic::type _minTip,
                     fuzzylogic::type _maxTip,
                     const std::string &filePath)
        : service(_service), food(_food), minTip(_minTip), maxTip(_maxTip) {

    std::ifstream file(filePath);

    fuzzyInterpreter.executeFile(file);

    file.close();
}

LeaveATip::LeaveATip()
        : LeaveATip(LEAVE_A_TIP_INTERPRETER_M_COG_FILE_PATH) {

}

LeaveATip::LeaveATip(const std::string &filePath)
        : LeaveATip(LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE,
                    LEAVE_A_TIP_DEFAULT_VALUE, filePath) {
}

void LeaveATip::setService(fuzzylogic::type _service) {
    service = _service;
}

void LeaveATip::setFood(fuzzylogic::type _food) {
    food = _food;
}

void LeaveATip::setMinTip(fuzzylogic::type _minTip) {
    minTip = _minTip;
}

void LeaveATip::setMaxTip(fuzzylogic::type _maxTip) {
    maxTip = _maxTip;
}

fuzzylogic::type LeaveATip::evaluateTip() {

    fuzzyInterpreter.writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, "Tip->service", service);
    fuzzyInterpreter.writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, "Tip->food", food);

    fuzzyInterpreter.executeLine(INTERPRETER_COMPUTE_COMMAND);

    fuzzylogic::type scaled = fuzzyInterpreter.readInMemory(fuzzylogic::AbstractInterpreter::OUTPUT, "Tip->tip") / 100;

    return (maxTip - minTip + 1.0) * scaled + minTip;
}
