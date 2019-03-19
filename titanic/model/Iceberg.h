
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include <cmath>

#include "PhysicObject2D.h"

#define NB_POINTS 1000

#define ICEBERG_WEIGHT 1000.0

namespace model {

    class Iceberg : public PhysicObject2D {

    private:
        std::vector<std::array<double, 2>> buildPointBounds(double r, unsigned int np);

    public:
        explicit Iceberg(double x, double y, double r);
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
