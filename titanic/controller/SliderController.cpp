
#define _USE_MATH_DEFINES

#include <iostream>
#include "SliderController.h"

namespace controller {

    SliderController::SliderController(Model *_model, View *_view, Draftsman *_draftsman) : AbstractController(_model,
                                                                                                               _view,
                                                                                                               _draftsman) {
    }

    void SliderController::machinePowerSliderValueChanged(int value) {

        double power = value * 1.0 / SLIDER_MAX_VALUE;

        std::cout << power << " " << value << std::endl;

        model->getTitanic()->setMachinePower(power);
    }

    void SliderController::helmSliderValueChanged(int value) {

        double angle = value * 1.0 / SLIDER_MAX_VALUE;

        model->getTitanic()->setRudderValue(angle);
    }
}