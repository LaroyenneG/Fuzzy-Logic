
#include "CheckBoxController.h"

namespace controller {
    CheckBoxController::CheckBoxController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman) {

    }

    void CheckBoxController::automaticPilotStateChange(bool checked) {

        if (checked) {
            view->enableAutomaticPilot();
        } else {
            view->disableAutomaticPilot();
            view->unlockDashboard();
        }
    }
}
