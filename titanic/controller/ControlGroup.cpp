
#include "ControlGroup.h"


namespace controller {

    ControlGroup::ControlGroup(model::Model *_model, view::View *_view)
            : model(_model), view(_view), draftsman(new view::Draftsman(model, view->getScene())),
              checkBoxController(nullptr), automaticPilotController(nullptr) {

        checkBoxController = new CheckBoxController(model, view, draftsman);
        automaticPilotController = new AutomaticPilotController(model, view, draftsman);
    }

    ControlGroup::~ControlGroup() {
        delete automaticPilotController;
        delete checkBoxController;
        delete draftsman;
    }
}