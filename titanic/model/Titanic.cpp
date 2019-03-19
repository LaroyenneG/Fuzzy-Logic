
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::set<std::array<double, MODEL_SPACE_DIMENSION>> Titanic::DEFAULT_POINTS{{0.0,   0.0},
                                                                                      {-14.0, 30},
                                                                                      {14.0,  30.0},
                                                                                      {-14,   218.0},
                                                                                      {14.0,  218.0},
                                                                                      {0.0,   269.0}};

    Titanic::Titanic(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &points, double _course, double _weight)
            : PhysicObject2D(points, 0, 0, _weight),
              course(_course),
              rudder(), engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {

    }

    Titanic::Titanic()
            : Titanic(DEFAULT_POINTS, DEFAULT_COURSE, TITANIC_DEFAULT_WEIGHT) {

    }

    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }
}