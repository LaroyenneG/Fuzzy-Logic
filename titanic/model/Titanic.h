
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <vector>

#include "Object2D.h"

namespace model {

    class Titanic : public Object2D {

    public:
        Titanic() : Object2D(std::set<std::pair<double, double >>()) {}
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
