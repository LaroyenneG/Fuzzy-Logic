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

        view->lockDashboard();

        view->disableAutomaticPilot();
        model->reproduceRealScene();
        view->setMachinePower(0.0);
        view->setHelmValue(SLIDER_MINIMUM_VALUE);
    }

    void MenuController::icebergScene() {

        view->unlockDashboard();
    }
}