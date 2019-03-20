
#ifndef LOGIQUEFLOUE_DRAFTSMAN_H
#define LOGIQUEFLOUE_DRAFTSMAN_H

#include <QtWidgets/QGraphicsScene>

#include "Model.h"

namespace view {

    class Draftsman {

    private:
        static const QColor SEA_COLOR;

        const model::Model *model;
        QGraphicsScene *scene;

        static QPoint scaleConverter(double x, double y);

    public:
        explicit Draftsman(const model::Model *_model, QGraphicsScene *_scene);

        void draw();

        void drawElement(const model::PhysicObject2D *object);

        ~Draftsman() = default;
    };
}


#endif //LOGIQUEFLOUE_DRAFTSMAN_H
