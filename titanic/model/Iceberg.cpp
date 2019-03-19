
#include "Iceberg.h"

#define _USE_MATH_DEFINES


namespace model {

    Iceberg::Iceberg(double x, double y, double r, double _weight)
            : PhysicObject2D(buildPoints(r, NB_POINTS), x, y, _weight) {

    }

    Iceberg::Iceberg(double x, double y) : Iceberg(x, y, DEFAULT_ICEBERG_RAYON, DEFAULT_ICEBERG_WEIGHT) {

    }

    Iceberg::Iceberg() : Iceberg(DEFAULT_ICEBERG_X, DEFAULT_ICEBERG_Y) {

    }

    std::vector<std::array<double, 2>> Iceberg::buildPoints(double r, unsigned int np) {

        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> points;

        for (unsigned int i = 0; i < np; ++i) {

            double a = M_PI * (i * 1.0 / np);

            std::array<double, MODEL_SPACE_DIMENSION> point{cos(a) * r, sin(a) * r};

            points.push_back(point);
        }

        return points;
    }
}