
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model *_model, View *_view, Draftsman *_draftsman)
            : draftsman(_draftsman), model(_model), view(_view) {

    }

    void AbstractController::updateView() {

        view->getMutex().lock();

        draftsman->draw();

        auto rotationSpeed = model->getTitanic()->getMachinesRotationSpeed();

        view->setMachinesSpeed(rotationSpeed[TITANIC_ALTERNATIVE_MACHINE_1_RANK],
                               rotationSpeed[TITANIC_TURBINE_MACHINE_RANK],
                               rotationSpeed[TITANIC_ALTERNATIVE_MACHINE_2_RANK]);

        view->setShipSpeed(model->getTitanic()->getSpeed());

        view->setDistance(model->distance());

        view->setCourse(model->getTitanic()->getOrientation());

        auto lasers = model->getTitanic()->getLasersValues(model->getElements());

        view->setLasersValue(lasers[0], lasers[1], lasers[2]);

        view->getMutex().unlock();
    }
}