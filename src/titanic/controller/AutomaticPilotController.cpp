

#include <iostream>
#include "AutomaticPilotController.h"

namespace controller {

    AutomaticPilotController::AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman), interpreter(new fuzzylogic::FuzzyInterpreter()) {

        std::ifstream fstream(AUTO_CONTROLLER_INTERPRETER_FILE_PATH);

        interpreter->executeFile(fstream);

        fstream.close();
    }

    void AutomaticPilotController::compute() {

        mutex.lock();

        auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());

        interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_1_FULL_NAME,
                                   lasers[TITANIC_LASER_1_RANK]);
        interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_2_FULL_NAME,
                                   lasers[TITANIC_LASER_2_RANK]);
        interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_3_FULL_NAME,
                                   lasers[TITANIC_LASER_3_RANK]);

        interpreter->execute(INTERPRETER_COMPUTE);

        double helmValue = interpreter->readInMemory(fuzzylogic::AbstractInterpreter::OUTPUT,
                                                     AUTO_PILOT_HELM_FULL_NAME);

        view->setHelmValue(helmValue);

        mutex.unlock();
    }

    AutomaticPilotController::~AutomaticPilotController() {

        delete interpreter;
    }
}