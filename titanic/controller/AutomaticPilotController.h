#ifndef LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
#define LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H


#include "AbstractController.h"

namespace controller {

    class AutomaticPilotController : public AbstractController {

        AutomaticPilotController() : AbstractController(nullptr, nullptr, nullptr) {}
    };
}

#endif //LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
