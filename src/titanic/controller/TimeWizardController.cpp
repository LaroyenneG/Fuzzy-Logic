
#include "TimeWizardController.h"

namespace controller {

    TimeWizardController::TimeWizardController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman), thread([] {}) {

    }

    void TimeWizardController::nextTime() {

        thread.join();

        updateView();

        thread = std::thread([this] { computeFuture(); });
    }

    void TimeWizardController::computeFuture() {

        mutex.lock();

        model->computeFuture(view->getTimeInterval() * TIME_WIZARD_CONTROLLER_TIME_CONVERTER);

        mutex.unlock();
    }
}