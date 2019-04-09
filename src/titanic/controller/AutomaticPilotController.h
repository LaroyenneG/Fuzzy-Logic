#ifndef LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
#define LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H


#include "FuzzyInterpreter.h"
#include "AbstractController.h"

namespace controller {

    class AutomaticPilotController : public AbstractController {

    Q_OBJECT

    private:
        interpreter::FuzzyInterpreter<double> fuzzyInterpreter;

    public:
        explicit AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman);

        ~AutomaticPilotController() override = default;

    public slots:

        void compute();
    };
}

#endif //LOGIQUEFLOUE_AUTOMATICPILOTCONTROLLER_H
