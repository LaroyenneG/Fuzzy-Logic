
#ifndef LOGIQUEFLOUE_ABSTRACTCONTROLER_H
#define LOGIQUEFLOUE_ABSTRACTCONTROLER_H

#include <QWidget>
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
        mutable std::mutex mutex;

        Model *model;
        View *view;

        void updateView() const;

    public:
        explicit AbstractController(Model *_model, View *_view, Draftsman *_draftsman);

        ~AbstractController() override = default;
    };
}


#endif //LOGIQUEFLOUE_ABSTRACTCONTROLER_H
