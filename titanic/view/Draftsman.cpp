
#include "Draftsman.h"


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
    }

    void Draftsman::drawElement(const model::PhysicObject2D *object) {

        std::vector<model::Point> points;

        object->writeAbsolutePoints(points);

        for (unsigned int i = 0; !points.empty() && i < points.size() - 1; ++i) {

            QPoint qp1 = scaleConverter(points[i][X_DIM_VALUE], points[i][Y_DIM_VALUE]);
            QPoint qp2 = scaleConverter(points[i + 1][X_DIM_VALUE], points[i + 1][Y_DIM_VALUE]);

            QLine qLine(qp1, qp2);

            scene->addLine(qLine, QPen(Qt::black));
        }
    }

    QPoint Draftsman::scaleConverter(double x, double y) {

        QPoint point(static_cast<int>(x * DRAFTSMAN_SCALE), static_cast<int>(y * DRAFTSMAN_SCALE));

        return point;
    }

    void Draftsman::drawVectors() {

        auto titanic = model->getTitanic();

        QLine accelerationLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                               scaleConverter(titanic->getAccelerationX() * 100.0 + titanic->getPositionX(),
                                              titanic->getAccelerationY() * 100.0 + titanic->getPositionY()));

        scene->addLine(accelerationLine, QPen(Qt::green));


        QLine speedLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                        scaleConverter(titanic->getSpeedX() * 10.0 + titanic->getPositionX(),
                                       titanic->getSpeedY() * 10.0 + titanic->getPositionY()));


        scene->addLine(speedLine, QPen(Qt::black));

        model::Vector lift = titanic->computeLift(0.0);

        QLine liftLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                       scaleConverter(lift[0] * 0.0001 + titanic->getPositionX(),
                                      lift[1] * 0.0001 + titanic->getPositionY()));

        scene->addLine(liftLine, QPen(Qt::red));

        model::Vector engine = titanic->computePropulsion(0.000001);

        QLine engineLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                         scaleConverter(engine[0] + titanic->getPositionX(),
                                        engine[1] + titanic->getPositionY()));

        scene->addLine(engineLine, QPen(Qt::yellow));
    }

    void Draftsman::drawTitanic(const model::Titanic *titanic) {

        const static QImage TITANIC_IMAGE(TITANIC_PICTURE_FILE_NAME);
        const static QPoint DIMENSION = scaleConverter(TITANIC_SIZE, TITANIC_WIDTH);


        drawLaserSensor(titanic->getLaserSensor());

        QGraphicsPixmapItem *titanicItem = new QGraphicsPixmapItem(
                QPixmap::fromImage(TITANIC_IMAGE).scaled(DIMENSION.x(), DIMENSION.y()));

        QTransform rotation;
        rotation.rotateRadians(titanic->getOrientation());

        QPoint position = scaleConverter(titanic->getPositionX() + TITANIC_WIDTH / 2.0,
                                         titanic->getPositionY() - TITANIC_SIZE / 2.0);

        QTransform translation;
        translation.translate(position.x(), position.y());

        QTransform transform = rotation * translation;

        titanicItem->setTransform(transform);

        scene->addItem(titanicItem);
    }

    void Draftsman::drawIceberg(const model::Iceberg *iceberg) {


        const static QImage ICEBERG_IMAGE(ICEBERG_IMAGE_FILE);
        const static QPoint DIMENSION = scaleConverter(ICEBERG_DEFAULT_RAYON * 2.0, ICEBERG_DEFAULT_RAYON * 2.0);

        QGraphicsPixmapItem *icebergItem = new QGraphicsPixmapItem(
                QPixmap::fromImage(ICEBERG_IMAGE).scaled(DIMENSION.x(), DIMENSION.y()));

        QPoint position = scaleConverter(iceberg->getPositionX() - ICEBERG_DEFAULT_RAYON,
                                         iceberg->getPositionY() - ICEBERG_DEFAULT_RAYON);

        QTransform translation;
        translation.translate(position.x(), position.y());

        icebergItem->setTransform(translation);

        scene->addItem(icebergItem);
    }

    void Draftsman::drawLaserSensor(const model::LasersSensor<TITANIC_LASERS_COUNTER> &laserSensor) {

        auto lines = laserSensor.getLaserLines(model->getElements());

        for (auto line : lines) {

            QPoint qp1 = scaleConverter(line.first[X_DIM_VALUE], line.first[Y_DIM_VALUE]);
            QPoint qp2 = scaleConverter(line.second[X_DIM_VALUE], line.second[Y_DIM_VALUE]);

            QLine qLine(qp1, qp2);

            scene->addLine(qLine, QPen(Qt::red));
        }
    }
}