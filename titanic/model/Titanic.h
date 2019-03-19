
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <vector>

#include "PhysicObject2D.h"
#include "Engine.h"
#include "Rudder.h"

#define DEFAULT_COURSE 0.0
#define DEFAULT_RUDDER 0.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0

#define ENGINES_COUNTER 3

namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const static std::vector<std::array<double, MODEL_SPACE_DIMENSION>> DEFAULT_POINTS;

        double course;  // radian

        Rudder rudder;

        const std::array<Engine *, ENGINES_COUNTER> engines;

    public:
        explicit Titanic(const std::vector<std::array<double, 2>> &points, double _course, double _weight,
                         double _xPosition, double _yPosition);

        explicit Titanic();

        ~Titanic() override;
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
