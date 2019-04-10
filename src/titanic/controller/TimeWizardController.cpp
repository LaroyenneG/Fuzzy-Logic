
#include "TimeWizardController.h"

namespace controller {

    TimeWizardController::TimeWizardController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {

    }

    void TimeWizardController::nextTime() {

        updateView();

        model->computeFuture(view->getTimeInterval() / 1000.0);

        if (model->touching()) {
            view->stopTime();
            view->touching();
        }
    }
}