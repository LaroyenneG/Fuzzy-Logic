#ifndef LOGIQUEFLOUE_CONTROLGROUP_H
#define LOGIQUEFLOUE_CONTROLGROUP_H


#include "Model.h"
#include "View.h"
#include "Draftsman.h"
#include "CheckBoxController.h"
#include "AutomaticPilotController.h"
#include "SliderController.h"
#include "TimeWizardController.h"

namespace controller {

    class ControlGroup {

    private:
        model::Model *model;
        view::View *view;
        view::Draftsman *draftsman;

        CheckBoxController *checkBoxController;
        AutomaticPilotController *automaticPilotController;
        SliderController *sliderController;
        TimeWizardController *timeWizardController;

        void setControllers() const;

    public:
        explicit ControlGroup(model::Model *_model, view::View *_view);

        ~ControlGroup();
    };
}

#endif //LOGIQUEFLOUE_CONTROLGROUP_H
