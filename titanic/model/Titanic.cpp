
#include <iostream>
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> Titanic::DEFAULT_POINTS{{{{0.0, 0.0}},
                                                                                                 {{30.0, -14.0}},
                                                                                                 {{218.0, -14.0}},
                                                                                                 {{269.0, 0.0}},
                                                                                                 {{218.0, 14.0}},
                                                                                                 {{30.0, 14.0}},
                                                                                                 {{0.0, 0.0}}}};

    Titanic::Titanic(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points, double _orientation,
                     double _weight,
                     double _xPosition, double _yPosition)
            : PhysicObject2D(points, _xPosition, _yPosition, _orientation, _weight),
              engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {
    }

    Titanic::Titanic() : Titanic(TITANIC_DEFAULT_X, TITANIC_DEFAULT_Y, TITANIC_DEFAULT_COURSE) {

    }

    Titanic::Titanic(double x, double y, double _orientation)
            : Titanic(DEFAULT_POINTS, _orientation, TITANIC_DEFAULT_WEIGHT, x, y) {

    }

    void Titanic::setRudderValue(double value) {
        rudder.setValue(value);
    }

    void Titanic::setMachinePower(double value) {
        engines[0]->setPower(value);
        engines[1]->setPower(value);
        engines[2]->setPower((value > 0.0) ? value : 0.0);
    }

    void Titanic::nextTime(double time) {


        double enginePush = 0.0; // N / kg
        for (auto engine : engines) {
            enginePush += engine->getPower();
        }

        double acceleration = enginePush; // m / s


        setAccelerationX(acceleration * cos(getOrientation()));
        setAccelerationY(-acceleration * sin(getOrientation()));

        PhysicObject2D::nextTime(time);
    }


    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }
}