
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model *_model, View *_view, Draftsman *_draftsman)
            : draftsman(_draftsman), model(_model), view(_view) {

    }

    void AbstractController::updateView() const {

        mutex.lock();

        draftsman->draw();

        auto rotationSpeed = model->getTitanic()->getMachinesRotationSpeed();

        view->setMachinesSpeed(rotationSpeed[TITANIC_ALTERNATIVE_MACHINE_1_RANK],
                               rotationSpeed[TITANIC_TURBINE_MACHINE_RANK],
                               rotationSpeed[TITANIC_ALTERNATIVE_MACHINE_2_RANK]);

        view->setShipSpeed(model->getTitanic()->getSpeed());

        view->setDistance(model->distance());

        view->setCourse(model->getTitanic()->getOrientation());

        if (view->automaticPilotIsEnable()) {

            draftsman->drawLaserSensor(&model->getTitanic()->getLasersSensors());

            auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());

            view->setLasersValue(lasers[TITANIC_LASER_1_RANK], lasers[TITANIC_LASER_2_RANK],
                                 lasers[TITANIC_LASER_3_RANK]);
        }

        if (model->touching()) {
            view->stopTime();
            view->touching();
        }

        mutex.unlock();
    }
}