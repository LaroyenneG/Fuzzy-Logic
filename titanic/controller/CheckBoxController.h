#ifndef LOGIQUEFLOUE_CONTROLER_H
#define LOGIQUEFLOUE_CONTROLER_H

#include <QObject>
#include "AbstractController.h"

namespace controller {

    class CheckBoxController : public AbstractController {

    Q_OBJECT

    public:
        explicit CheckBoxController(Model *_model, View *_view, Draftsman *_draftsman);

        ~CheckBoxController() override = default;

    public slots:

        void automaticPilotStateChange(bool checked);
    };
}

#endif //LOGIQUEFLOUE_CONTROLER_H
