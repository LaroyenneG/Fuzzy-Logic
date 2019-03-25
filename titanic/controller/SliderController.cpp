
#define _USE_MATH_DEFINES

#include "SliderController.h"

namespace controller {

    SliderController::SliderController(Model *_model, View *_view, Draftsman *_draftsman) : AbstractController(_model,
                                                                                                               _view,
                                                                                                               _draftsman) {
    }

    void SliderController::machinePowerSliderValueChanged(int value) {

        double power = value * 1.0 / SLIDER_MAX_VALUE;

        auto machines = model->getTitanic()->getMachinesRotationSpeed();

        bool canSet = true;

        for (auto &machine : machines) {

            double rot = machine;

            if (abs(rot) >= 0.1 && rot * power < 0) {
                canSet = false;
                break;
            }
        }

        if (canSet) {
            model->getTitanic()->setMachinePower(power);
        } else {
            model->getTitanic()->setMachinePower(0.0);
            view->setMachinePower(0.0);
        }
    }

    void SliderController::helmSliderValueChanged(int value) {

        double angle = (value * 1.0 / SLIDER_MAX_VALUE) * (M_PI / 4.0);

        model->getTitanic()->setRudderValue(angle);
    }
}