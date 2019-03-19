
#ifndef LOGIQUEFLOUE_DRAFTSMAN_H
#define LOGIQUEFLOUE_DRAFTSMAN_H

#include <QtWidgets/QGraphicsScene>
#include "Model.h"

using namespace model;

namespace view {

    class Draftsman {

    private:
        static const QColor SEA_COLOR;

        const Model &model;
        QGraphicsScene &qGraphicsScene;

    public:
        explicit Draftsman(const Model &_model, QGraphicsScene &_qGraphicsScene);

        void draw();

        ~Draftsman() = default;
    };
}


#endif //LOGIQUEFLOUE_DRAFTSMAN_H
