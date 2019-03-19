
#ifndef LOGIQUEFLOUE_ICEBERG_H
#define LOGIQUEFLOUE_ICEBERG_H

#include "Object2D.h"

namespace model {

    class Iceberg : public Object2D {

    public:
        Iceberg() : Object2D(Object2D(std::set<std::pair<double, double >>(), 0)) {}
    };
}

#endif //LOGIQUEFLOUE_ICEBERG_H
