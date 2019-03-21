
#include <iostream>
#include "SliderController.h"

namespace controller {


    SliderController::SliderController(Model *_model, View *_view, Draftsman *_draftsman) : AbstractController(_model,
                                                                                                               _view,
                                                                                                               _draftsman) {
    }

    void SliderController::machinePowerSliderValueChanged(int value) {

        double power = (value - SLIDER_MAX_VALUE / 2.0) / (SLIDER_MAX_VALUE / 2.0);

        model->getTitanic()->setMachinePower(power);
    }

    void SliderController::helmSliderValueChanged(int value) {

        double angle = (value - SLIDER_MAX_VALUE / 2.0) / (SLIDER_MAX_VALUE / 2.0);

        model->getTitanic()->setRudderValue(angle);

        std::cout << angle << std::endl;
    }
}