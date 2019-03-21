
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <cmath>
#include <vector>

#include "PhysicObject2D.h"
#include "Engine.h"
#include "Rudder.h"

#define TITANIC_DEFAULT_COURSE 0.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0
#define TITANIC_DEFAULT_X 0.0
#define TITANIC_DEFAULT_Y 0.0

#define ENGINES_COUNTER 3

namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const static std::vector<std::array<double, MODEL_SPACE_DIMENSION>> DEFAULT_POINTS;

        Rudder rudder;

        const std::array<Engine *, ENGINES_COUNTER> engines;

    public:
        explicit Titanic(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points, double _orientation,
                         double _weight,
                         double _xPosition, double _yPosition);

        explicit Titanic(double x, double y, double _orientation);

        explicit Titanic();

        ~Titanic() override;

        void nextTime(double time) override;

        void setMachinePower(double value);

        void setRudderValue(double value);
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
