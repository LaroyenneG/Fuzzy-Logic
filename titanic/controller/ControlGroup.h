#ifndef LOGIQUEFLOUE_CONTROLGROUP_H
#define LOGIQUEFLOUE_CONTROLGROUP_H


#include "Model.h"
#include "View.h"
#include "Draftsman.h"
#include "CheckBoxController.h"
#include "AutomaticPilotController.h"

namespace controller {

    class ControlGroup {

    private:
        model::Model *model;
        view::View *view;
        view::Draftsman *draftsman;

        CheckBoxController *checkBoxController;
        AutomaticPilotController *automaticPilotController;

    public:
        explicit ControlGroup(model::Model *_model, view::View *_view);

        ~ControlGroup();
    };
}

#endif //LOGIQUEFLOUE_CONTROLGROUP_H
