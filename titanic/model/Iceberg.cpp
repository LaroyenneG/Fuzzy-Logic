
#include "Iceberg.h"

#define _USE_MATH_DEFINES


namespace model {

    Iceberg::Iceberg(double x, double y, double r, double _weight)
            : PhysicObject2D(buildPoints(r, NB_POINTS), x, y, DEFAULT_ORIENTATION, _weight) {

    }

    Iceberg::Iceberg(double x, double y) : Iceberg(x, y, DEFAULT_ICEBERG_RAYON, DEFAULT_ICEBERG_WEIGHT) {

    }

    Iceberg::Iceberg() : Iceberg(DEFAULT_ICEBERG_X, DEFAULT_ICEBERG_Y) {

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
}