
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

        for (auto rotationSpeed : machinesRotationSpeed) {

            if (abs(rotationSpeed) >= 0.3 && rotationSpeed * power < 0) {
                canChange = false;
                break;
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

        double angle = (value * -1.0 / SLIDER_MAX_VALUE) * (M_PI / 4.0);

        model->getTitanic()->setRudderValue(angle);
    }
}