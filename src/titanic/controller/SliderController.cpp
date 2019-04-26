
#define _USE_MATH_DEFINES

#include "SliderController.h"

namespace controller {

    SliderController::SliderController(Model *_model, View *_view, Draftsman *_draftsman) : AbstractController(_model,
                                                                                                               _view,
                                                                                                               _draftsman) {
    }

    void SliderController::machinePowerSliderValueChanged(int value) {

        double power = value * 1.0 / SLIDER_MAX_VALUE;

        auto machinesRotationSpeed = model->getTitanic()->getMachinesRotationSpeed();

        bool canChange = true;

        for (unsigned int i = 0; i < machinesRotationSpeed.size(); i++) {

            if (i != TITANIC_TURBINE_MACHINE_RANK) {

                if (fabs(machinesRotationSpeed[i]) >= 0.1 && machinesRotationSpeed[i] * power < 0) {
                    canChange = false;
                    break;
                }
            }
        }

        if (canChange) {
            model->getTitanic()->setMachinePower(power);
        } else {
            model->getTitanic()->setMachinePower(0.0);
            view->setMachinePower(0.0);
        }
    }

    void SliderController::helmSliderValueChanged(int value) {

        double angle = (value * -1.0 / SLIDER_MAX_VALUE) * (M_PI / 6.0);

        model->getTitanic()->setRudderValue(angle);
    }
}