
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include "PhysicObject2D.h"

namespace model {

    class Iceberg : public PhysicObject2D {

    private:


    public:
        explicit Iceberg(const PhysicObject2D &object, double x, double y, double rayon);
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
