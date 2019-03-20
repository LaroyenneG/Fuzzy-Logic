
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> Titanic::DEFAULT_POINTS{{{{0.0, 0.0}},
                                                                                                 {{-14.0, 30}},
                                                                                                 {{14.0, 30.0}},
                                                                                                 {{-14, 218.0}},
                                                                                                 {{14.0, 218.0}},
                                                                                                 {{0.0, 269.0}},
                                                                                                 {{0.0, 0.0}}}};

    Titanic::Titanic(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points, double _course,
                     double _weight,
                     double _xPosition, double _yPosition)
            : PhysicObject2D(points, _xPosition, _yPosition, _course, _weight),
              engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {
    }

    Titanic::Titanic() : Titanic(TITANIC_DEFAULT_X, TITANIC_DEFAULT_Y, TITANIC_DEFAULT_COURSE) {

    }

    Titanic::Titanic(double x, double y, double course)
            : Titanic(DEFAULT_POINTS, course, TITANIC_DEFAULT_WEIGHT, x, y) {

    }

    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }
}