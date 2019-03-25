
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model *_model, View *_view, Draftsman *_draftsman)
            : draftsman(_draftsman), model(_model), view(_view) {

    }

    void AbstractController::updateView() {

        view->getMutex().lock();

        draftsman->draw();

        draftsman->drawVectors();

        auto rotationSpeed = model->getTitanic()->getMachinesRotationSpeed();

        view->setMachinesSpeed(rotationSpeed[0], rotationSpeed[2], rotationSpeed[1]);

        view->setShipSpeed(model->getTitanic()->getSpeed());

        view->setDistance(model->distance());

        view->getMutex().unlock();
    }
}