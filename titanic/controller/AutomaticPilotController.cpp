

#include <iostream>
#include "AutomaticPilotController.h"

namespace controller {

    AutomaticPilotController::AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {


    }

    void AutomaticPilotController::compute() {

        view->setHelmValue(-5.0);

        std::cout << "pilot auto beep" << std::endl;
    }
}