
#include "TimeWizardController.h"

namespace controller {

    TimeWizardController::TimeWizardController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {

    }

    void TimeWizardController::nextTime() {

        updateView();

        std::cout << model->getTitanic()->getMachinesRotationSpeed()[0] * 9.54 << "; "
                  << model->getTitanic()->getMachinesRotationSpeed()[2] * 9.54 << std::endl;

        model->getTitanic()->nextTime(DEFAULT_VIEW_TIMER_INTERVAL / 1000.0);

        if (model->touching()) {
            view->stopTime();
            view->touching();
        }
    }
}