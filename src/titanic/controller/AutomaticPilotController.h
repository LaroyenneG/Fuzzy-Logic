#ifndef LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
#define LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H

#define AUTO_CONTROLLER_INTERPRETER_FILE_PATH "../assets/automatic-pilot.fuzzy"

#define AUTO_PILOT_LAZER_1_FULL_NAME "Helm->laser1"
#define AUTO_PILOT_LAZER_2_FULL_NAME "Helm->laser2"
#define AUTO_PILOT_LAZER_3_FULL_NAME "Helm->laser3"
#define AUTO_PILOT_HELM_FULL_NAME "Helm->value"


#include "fuzzylogic.h"

#include "AbstractController.h"

namespace controller {

    class AutomaticPilotController : public AbstractController {

    Q_OBJECT

    private:
        fuzzylogic::AbstractInterpreter *interpreter;

    public:
        explicit AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman);

        ~AutomaticPilotController() override;

    public slots:

        void compute();
    };
}

#endif //LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
