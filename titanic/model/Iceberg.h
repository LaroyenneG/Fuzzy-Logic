
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include <cmath>

#include "PhysicObject2D.h"

#define NB_POINTS 1000
#define DEFAULT_ICEBERG_X 0.0
#define DEFAULT_ICEBERG_Y 0.0
#define DEFAULT_ICEBERG_RAYON 60.0          // m
#define DEFAULT_ICEBERG_WEIGHT 1500000000   // kg

namespace model {

    class Iceberg : public PhysicObject2D {

    private:
        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> buildPoints(double r, unsigned int np);

    public:
        explicit Iceberg(double x, double y, double r, double _weight);

        explicit Iceberg(double x, double y);

        explicit Iceberg();
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
