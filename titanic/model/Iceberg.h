
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include "Object2D.h"

namespace model {

    class Iceberg : public Object2D {

    private:


    public:
        explicit Iceberg(const Object2D &object, double x, double y, double rayon);
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
