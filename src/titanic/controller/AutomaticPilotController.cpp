
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

        static const double DANGER_VALUE = 1 - pow(10, -5);

        mutex.lock();

        bool danger = false;

        auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());
        for (auto &laser : lasers) {
            if (laser < DANGER_VALUE) {
                danger = true;
            } else if (laser >= 1.0) {
                laser = DANGER_VALUE;
            }
        }

        double helmValue = 0.0;

        if (danger) {

            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_1_FULL_NAME,
                                       lasers[TITANIC_LASER_1_RANK]);
            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_2_FULL_NAME,
                                       lasers[TITANIC_LASER_2_RANK]);
            interpreter->writeInMemory(fuzzylogic::AbstractInterpreter::INPUT, AUTO_PILOT_LAZER_3_FULL_NAME,
                                       lasers[TITANIC_LASER_3_RANK]);

            interpreter->executeLine(INTERPRETER_COMPUTE_COMMAND);

            helmValue = interpreter->readInMemory(fuzzylogic::AbstractInterpreter::OUTPUT,
                                                  AUTO_PILOT_HELM_FULL_NAME);

            helmValue = (helmValue * 2.0 - 1.0) * SLIDER_MAXIMUM_VALUE;

            view->setMachinePower(SLIDER_MINIMUM_VALUE);

        } else {

            view->setMachinePower(SLIDER_MAXIMUM_VALUE - 5.0);
        }

        view->setHelmValue(helmValue);

        mutex.unlock();
    }

    AutomaticPilotController::~AutomaticPilotController() {

        delete interpreter;
    }
}