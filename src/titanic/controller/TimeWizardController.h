#ifndef LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H
#define LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H

#include <QMessageBox>
#include <thread>

#include "AbstractController.h"

#define TIME_WIZARD_CONTROLLER_TIME_CONVERTER (1.0/1000.0)

namespace controller {

    class TimeWizardController : public AbstractController {

    Q_OBJECT

    private:
        std::thread thread;

        void computeFuture();

    public:
        explicit TimeWizardController(Model *_model, View *_view, Draftsman *_draftsman);

        ~TimeWizardController() override = default;

    public slots:

        void nextTime();
    };
}


#endif //LOGIQUEFLOUE_TIMEWIZARDCONTROLLER_H
