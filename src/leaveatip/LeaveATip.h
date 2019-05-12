#ifndef LOGIQUEFLOUE_LEAVEATIP_H
#define LOGIQUEFLOUE_LEAVEATIP_H

#define LEAVE_A_TIP_INTERPRETER_M_COG_FILE_PATH "../assets/leaveatip_cog.fuzzy"
#define LEAVE_A_TIP_INTERPRETER_MSUGENO_FILE_PATH "../assets/leaveatip_sugeno.fuzzy"
#define LEAVE_A_TIP_DEFAULT_VALUE 0.0
#define LEAVE_A_TIP_SERVICE_VARIABLE_NAME "Tip->service"
#define LEAVE_A_TIP_FOOD_VARIABLE_NAME "Tip->food"
#define LEAVE_A_TIP_TIP_VARIABLE_NAME "Tip->tip"


#include "fuzzylogic.h"


class LeaveATip {

private:
    fuzzylogic::FuzzyInterpreter fuzzyInterpreter;

    fuzzylogic::type service;
    fuzzylogic::type food;

public:
    explicit LeaveATip(fuzzylogic::type _service, fuzzylogic::type _food, const std::string &filePath);

    explicit LeaveATip();

    explicit LeaveATip(const std::string &filePath);

    void setService(fuzzylogic::type _service);

    void setFood(fuzzylogic::type _food);
    fuzzylogic::type evaluateTip();
};


#endif //LOGIQUEFLOUE_LEAVEATIP_H
