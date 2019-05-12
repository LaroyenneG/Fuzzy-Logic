#include "LeaveATip.h"

LeaveATip::LeaveATip(fuzzylogic::type _service, fuzzylogic::type _food, const std::string &filePath)
        : service(_service), food(_food) {

    std::ifstream file(filePath);

    fuzzyInterpreter.executeFile(file);

    file.close();
}

LeaveATip::LeaveATip()
        : LeaveATip(LEAVE_A_TIP_INTERPRETER_M_COG_FILE_PATH) {

}

LeaveATip::LeaveATip(const std::string &filePath)
        : LeaveATip(LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE, filePath) {
}

void LeaveATip::setService(fuzzylogic::type _service) {
    service = _service;
}

void LeaveATip::setFood(fuzzylogic::type _food) {
    food = _food;
}


fuzzylogic::type LeaveATip::evaluateTip() {

    fuzzyInterpreter.writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, LEAVE_A_TIP_SERVICE_VARIABLE_NAME, service);
    fuzzyInterpreter.writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, LEAVE_A_TIP_FOOD_VARIABLE_NAME, food);

    fuzzyInterpreter.executeLine(INTERPRETER_COMPUTE_COMMAND);

    return fuzzyInterpreter.readInMemory(fuzzylogic::AbstractInterpreter::OUTPUT, LEAVE_A_TIP_TIP_VARIABLE_NAME);
}
