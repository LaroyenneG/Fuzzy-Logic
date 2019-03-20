
#include "ControlGroup.h"


namespace controller {

    ControlGroup::ControlGroup(model::Model *_model, view::View *_view)
            : model(_model), view(_view), draftsman(new view::Draftsman(model, view->getScene())), checkBoxController(
            new CheckBoxController(_model, view, draftsman)) {

    }

    ControlGroup::~ControlGroup() {
        delete checkBoxController;
        delete draftsman;
    }
}