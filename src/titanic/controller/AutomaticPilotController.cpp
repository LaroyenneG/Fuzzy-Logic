

#include <iostream>
#include "AutomaticPilotController.h"

namespace controller {

    AutomaticPilotController::AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {

        std::ifstream fstream(AUTO_CONTROLLER_INTERPRETER_FILE_PATH);

        fuzzyInterpreter.executeFile(fstream);

        fstream.close();
    }

    void AutomaticPilotController::compute() {

        mutex.lock();

        /* to completed */

        mutex.unlock();
    }
}