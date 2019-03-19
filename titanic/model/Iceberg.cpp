
#include "Iceberg.h"

#define _USE_MATH_DEFINES


namespace model {

    Iceberg::Iceberg(double x, double y, double r)
            : PhysicObject2D(buildPointBounds(r, NB_POINTS), x, y, ICEBERG_WEIGHT) {

    }

    std::set<std::array<double, MODEL_SPACE_DIMENSION>> Iceberg::buildPointBounds(double r, unsigned int np) {

        std::set<std::array<double, MODEL_SPACE_DIMENSION>> points;

        for (unsigned int i = 0; i < np; ++i) {

            double a = M_PI * (i * 1.0 / np);

            std::array<double, MODEL_SPACE_DIMENSION> point{cos(a) * r, sin(a) * r};

            points.insert(point);
        }

        return points;
    }
}