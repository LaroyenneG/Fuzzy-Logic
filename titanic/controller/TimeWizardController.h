#ifndef LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H
#define LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H

#include "AbstractController.h"

namespace controller {

    class TimeWizardController : public AbstractController {

    Q_OBJECT

    public:
        explicit TimeWizardController(Model *_model, View *_view, Draftsman *_draftsman);

        ~TimeWizardController() override = default;

    public slots:

        void nextTime();
    };
}


#endif //LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H
