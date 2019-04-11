

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

        view->getMutex().lock();

        auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());

        view->setLasersValue(lasers[TITANIC_LASER_1_RANK], lasers[TITANIC_LASER_2_RANK], lasers[TITANIC_LASER_3_RANK]);

        view->getMutex().unlock();
    }
}