
#include <iostream>
#include "SliderController.h"

namespace controller {
    SliderController::SliderController(Model *_model, View *_view, Draftsman *_draftsman) : AbstractController(_model,
                                                                                                               _view,
                                                                                                               _draftsman) {
    }

    void SliderController::machinePowerSliderValueChanged(int value) {
        updateView();
        std::cout << value << '\n';
    }

    void SliderController::helmSliderValueChanged(int value) {
        std::cout << value << '\n';
    }
}