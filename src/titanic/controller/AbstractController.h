
#ifndef LOGIQUEFLOUE_ABSTRACTCONTROLER_H
#define LOGIQUEFLOUE_ABSTRACTCONTROLER_H

#include <QObject>
#include <mutex>

#include "Model.h"
#include "View.h"
#include "Draftsman.h"

namespace controller {

    using namespace model;
    using namespace view;

    class AbstractController : public QWidget {

    private:
        Draftsman *draftsman;

    protected:
        Model *model;
        View *view;

        void updateView();

    public:
        explicit AbstractController(Model *_model, View *_view, Draftsman *_draftsman);

        virtual ~AbstractController() = default;
    };
}


#endif //LOGIQUEFLOUE_ABSTRACTCONTROLER_H
