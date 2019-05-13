#include "MenuController.h"

namespace controller {

    MenuController::MenuController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {

    }

    void MenuController::reset() {

        view->stopTime();

        view->unlockDashboard();

        model->resetToDefault();

        view->setHelmValue(0);
        view->setMachinePower(0);
        view->disableAutomaticPilot();

        view->startTime();

        updateView();
    }

    void MenuController::pause() {

        view->stopTime();
    }

    void MenuController::play() {

        view->startTime();
    }

    void MenuController::acceleration() {

        double value = QInputDialog::getDouble(view, QString("Acceleration"), QString("Value [0.25, 3.0] :"),
                                               1.0,
                                               0.25,
                                               3.0);

        model->setTimeAcceleration(value);
    }

    void MenuController::realIcebergScene() {

        reset();

        model->getTitanic()->reachMachinePower(1.0);

        view->lockDashboard();

        view->disableAutomaticPilot();
        model->reproduceRealScene();
        view->setHelmValue(SLIDER_MINIMUM_VALUE);
        view->setMachinePower(0);
    }

    void MenuController::icebergScene() {

        reset();

        view->unlockDashboard();
        model->icebergScene();
        view->setHelmValue(0);
        view->setMachinePower(SLIDER_MAXIMUM_VALUE);
        view->enableAutomaticPilot();
    }
}