
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include <cmath>

#include "PhysicObject2D.h"

#define ICEBERG_NB_POINTS 100
#define ICEBERG_DEFAULT_X 20.0
#define ICEBERG_DEFAULT_Y 800.0
#define ICEBERG_DEFAULT_RAYON 60.0          // m
#define ICEBERG_DEFAULT_WEIGHT 1500000000   // kg

#define ICEBERG_IMAGE_FILE "../assets/iceberg.png"

namespace model {

    class Iceberg : public PhysicObject2D {

    private:
        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> buildPoints(double r, unsigned int np);

    public:
        explicit Iceberg(double x, double y, double r, double _weight);

        explicit Iceberg(double x, double y);

        explicit Iceberg();

        void drawMe(view::Draftsman *draftsman) override;

        ~Iceberg() override = default;
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
