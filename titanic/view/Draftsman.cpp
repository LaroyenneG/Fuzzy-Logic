
#include "Draftsman.h"

#define SCALE 2.0

namespace view {

    const QColor Draftsman::SEA_COLOR(0, 138, 230);

    Draftsman::Draftsman(const model::Model *_model, QGraphicsScene *_scene)
            : model(_model), scene(_scene) {

        scene->setBackgroundBrush(SEA_COLOR);
    }

    void Draftsman::draw() {

        scene->clear();

        for (auto element : model->getElements()) {
            element->drawMe(this);
        }

        drawVector();
    }

    void Draftsman::drawElement(const model::PhysicObject2D *object) {

        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> points;

        object->writeAbsolutePoints(points);

        for (unsigned int i = 0; i < points.size() - 1; ++i) {

            auto &p1 = points[i];
            auto &p2 = points[i + 1];

            QPoint qp1 = scaleConverter(p1[X_DIM_VALUE], p1[Y_DIM_VALUE]);
            QPoint qp2 = scaleConverter(p2[X_DIM_VALUE], p2[Y_DIM_VALUE]);

            QLine line(qp1, qp2);

            scene->addLine(line);
        }
    }

    QPoint Draftsman::scaleConverter(double x, double y) {

        QPoint point(static_cast<int>(x * SCALE), static_cast<int>(y * SCALE));

        return point;
    }

    void Draftsman::drawVector() {

        auto titanic = model->getTitanic();

        QLine accLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                      scaleConverter(titanic->getAccelerationX() * 1000.0 + titanic->getPositionX(),
                                     titanic->getAccelerationY() * 1000.0 + titanic->getPositionY()));

        scene->addLine(accLine);


        QLine speedLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                        scaleConverter(titanic->getSpeedX() * 10.0 + titanic->getPositionX(),
                                       titanic->getSpeedY() * 10.0 + titanic->getPositionY()));

        scene->addLine(speedLine);
    }
}