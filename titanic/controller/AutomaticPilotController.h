#ifndef LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
#define LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H


#include "FuzzyInterpreter.h"
#include "AbstractController.h"

namespace controller {

    class AutomaticPilotController : public AbstractController {

    private:
        interpreter::FuzzyInterpreter<double> fuzzyInterpreter;

    public:
        explicit AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman);
    };
}

#endif //LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
