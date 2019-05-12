
#include "fuzzylogic.h"
#include <iostream>
#include <fuzzy/IsBornedTrapezoid.h>
#include "IsTrapezoid.h"
#include "IsTriangle.h"
#include "IsParable.h"
#include "IsBornedTrapezoid.h"
#include "ValueModel.h"
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

        bool danger = false;

        auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());
        for (auto laser : lasers) {
            if (laser < 1.0) {
                danger = true;
                break;
            }
        }

        if (danger) {

            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_1_FULL_NAME,
                                       lasers[TITANIC_LASER_1_RANK]);
            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_2_FULL_NAME,
                                       lasers[TITANIC_LASER_2_RANK]);
            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_3_FULL_NAME,
                                       lasers[TITANIC_LASER_3_RANK]);

            interpreter->executeLine(INTERPRETER_COMPUTE_COMMAND);

            double helmValue = interpreter->readInMemory(fuzzylogic::AbstractInterpreter::OUTPUT,
                                                         AUTO_PILOT_HELM_FULL_NAME);

            helmValue = helmValue * 2.0 - 1.0;

            view->setHelmValue(helmValue * SLIDER_MAXIMUM_VALUE);
        }

        mutex.unlock();

    }

    AutomaticPilotController::~AutomaticPilotController() {

        delete interpreter;
    }
}