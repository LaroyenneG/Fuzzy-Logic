
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <vector>

#include "Object2D.h"

#define DEFAULT_COURSE 0.0
#define DEFAULT_RUDDER 0.0
#define DEFAULT_PROPERLER 0.0
#define DEFAULT_ENGINE_POWER 0.0

namespace model {

    class Titanic : public Object2D {

    private:
        double course;          // radian
        double rudder;          // radian
        double propellerSpeed;      // radian / s
        double propellerAccelerator;    // radian / s²

    public:
        explicit Titanic(const std::set<std::pair<double, double >> &points, double _course, double _rudder,
                         double _propellerAccelerator, double _enginePower);
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
