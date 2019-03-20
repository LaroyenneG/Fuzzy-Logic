
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model *_model, View *_view, Draftsman *_draftsman)
            : draftsman(_draftsman), model(_model), view(_view) {

    }

    void AbstractController::updateView() {

        view->getMutex().lock();

        draftsman->draw();

        view->getMutex().unlock();
    }
}