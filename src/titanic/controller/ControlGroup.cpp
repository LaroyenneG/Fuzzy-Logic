
#include "ControlGroup.h"


namespace controller {

    ControlGroup::ControlGroup(model::Model *_model, view::View *_view)
            : model(_model), view(_view), draftsman(new view::Draftsman(model, view->getGraphicsScene())),
              checkBoxController(nullptr), automaticPilotController(nullptr), sliderController(nullptr),
              timeWizardController(nullptr), menuController(nullptr) {

        checkBoxController = new CheckBoxController(model, view, draftsman);
        automaticPilotController = new AutomaticPilotController(model, view, draftsman);
        sliderController = new SliderController(model, view, draftsman);
        timeWizardController = new TimeWizardController(model, view, draftsman);
        menuController = new MenuController(model, view, draftsman);

        setControllers();
    }

    void ControlGroup::setControllers() const {
        view->setSliderController(sliderController);
        view->setCheckBoxController(checkBoxController);
        view->setTimeWizardController(timeWizardController);
        view->setAutomaticPilotController(automaticPilotController);
        view->setMenuController(menuController);
    }

    ControlGroup::~ControlGroup() {
        delete menuController;
        delete sliderController;
        delete automaticPilotController;
        delete checkBoxController;
        delete draftsman;
    }
}