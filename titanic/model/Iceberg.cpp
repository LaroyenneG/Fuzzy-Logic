
#include "Draftsman.h"
#include "Iceberg.h"

#define _USE_MATH_DEFINES


namespace model {

    Iceberg::Iceberg(double x, double y, double r, double _weight)
            : PhysicObject2D(buildPoints(r, ICEBERG_NB_POINTS), x, y, DEFAULT_ORIENTATION, _weight) {

    }

    Iceberg::Iceberg(double x, double y) : Iceberg(x, y, ICEBERG_DEFAULT_RAYON, ICEBERG_DEFAULT_WEIGHT) {

    }

    Iceberg::Iceberg() : Iceberg(ICEBERG_DEFAULT_X, ICEBERG_DEFAULT_Y) {

    }

    std::vector<std::array<double, MODEL_SPACE_DIMENSION>> Iceberg::buildPoints(double r, unsigned int np) {

        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> points;

        for (unsigned int i = 0; i < np; ++i) {

            double angle = M_PI * (i * 2.0 / (np - 1));

            std::array<double, MODEL_SPACE_DIMENSION> point{cos(angle) * r, sin(angle) * r};

            points.push_back(point);
        }

        return points;
    }

    void Iceberg::drawMe(view::Draftsman *draftsman) {
        draftsman->drawIceberg(this);
    }
}