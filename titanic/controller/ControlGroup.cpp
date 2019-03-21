
#include "ControlGroup.h"


namespace controller {

    ControlGroup::ControlGroup(model::Model *_model, view::View *_view)
            : model(_model), view(_view), draftsman(new view::Draftsman(model, view->getScene())),
              checkBoxController(nullptr), automaticPilotController(nullptr), sliderController(nullptr),
              timeWizardController(
                      nullptr) {

        checkBoxController = new CheckBoxController(model, view, draftsman);
        automaticPilotController = new AutomaticPilotController(model, view, draftsman);
        sliderController = new SliderController(model, view, draftsman);
        timeWizardController = new TimeWizardController(model, view, draftsman);

        setControllers();
    }

    void ControlGroup::setControllers() const {
        view->setSliderController(sliderController);
        view->setCheckBoxController(checkBoxController);
        view->setTimeWizardController(timeWizardController);
    }

    ControlGroup::~ControlGroup() {
        delete sliderController;
        delete automaticPilotController;
        delete checkBoxController;
        delete draftsman;
    }
}