
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model *_model, View *_view, Draftsman *_draftsman)
            : mutex(_view->getMutex()), draftsman(_draftsman), model(_model), view(_view) {

    }

    void AbstractController::updateView() {

        mutex.lock();

        draftsman->draw();

        mutex.unlock();
    }
}