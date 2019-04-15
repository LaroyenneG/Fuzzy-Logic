
#include "Draftsman.h"
#include "Iceberg.h"

#define _USE_MATH_DEFINES

#include <math.h>


namespace model {

    Iceberg::Iceberg(double x, double y, double r, double _weight)
            : PhysicObject2D(buildCirclePoints(r, ICEBERG_NB_POINTS), x, y, DEFAULT_ORIENTATION, _weight) {

    }

    Iceberg::Iceberg(double x, double y) : Iceberg(x, y, ICEBERG_DEFAULT_RAYON, ICEBERG_DEFAULT_WEIGHT) {

    }

    Iceberg::Iceberg() : Iceberg(ICEBERG_DEFAULT_X, ICEBERG_DEFAULT_Y) {

    }

    std::vector<std::array<double, MODEL_SPACE_DIMENSION>> Iceberg::buildCirclePoints(double rayon,
                                                                                      unsigned int pointNumber) {

        std::vector<Point> points;

        for (unsigned int i = 0; i < pointNumber; ++i) {

            double angle = M_PI * (i * 2.0 / (pointNumber - 1));

            Point point{cos(angle) * rayon, sin(angle) * rayon};

            points.push_back(point);
        }

        return points;
    }

    void Iceberg::drawMe(view::Draftsman *draftsman) {
        draftsman->drawIceberg(this);
    }
}