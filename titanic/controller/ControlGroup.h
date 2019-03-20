#ifndef LOGIQUEFLOUE_CONTROLGROUP_H
#define LOGIQUEFLOUE_CONTROLGROUP_H


#include "Model.h"
#include "View.h"
#include "Draftsman.h"


namespace controller {

    class ControlGroup {

    private:
        model::Model *model;
        view::View *view;
        view::Draftsman *draftsman;

    public:
        explicit ControlGroup(model::Model *_model, view::View *_view);

        ~ControlGroup();
    };
}

#endif //LOGIQUEFLOUE_CONTROLGROUP_H
