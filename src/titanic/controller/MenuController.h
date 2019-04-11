
#ifndef LOGIQUEFLOUE_MENUCONTROLLER_H
#define LOGIQUEFLOUE_MENUCONTROLLER_H

#include "AbstractController.h"

#include <QInputDialog>

namespace controller {

    class MenuController : public AbstractController {

    Q_OBJECT

    public:
        explicit MenuController(Model *_model, View *_view, Draftsman *_draftsman);

        ~MenuController() override = default;

    public slots:

        void reset();

        void pause();

        void play();

        void acceleration();

        void realIcebergScene();

        void icebergScene();
    };
}


#endif //LOGIQUEFLOUE_MENUCONTROLLER_H
