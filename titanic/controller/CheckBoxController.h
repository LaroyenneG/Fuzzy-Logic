#ifndef LOGIQUEFLOUE_CONTROLER_H
#define LOGIQUEFLOUE_CONTROLER_H

#include <QObject>
#include "AbstractController.h"

namespace controller {

    class CheckBoxController : public AbstractController {

    public:
        explicit CheckBoxController(Model *_model, View *_view, Draftsman *_draftsman);

        void changeState();

        ~CheckBoxController() override = default;
    };
}

#endif //LOGIQUEFLOUE_CONTROLER_H
