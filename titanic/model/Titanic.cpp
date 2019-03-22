
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

        double enginePush = 0.0; // N / S
        for (auto engine : engines) {
            engine->nexTime(time);
            enginePush += engine->getPropulsionStrength();
        }

        std::array<double, MODEL_SPACE_DIMENSION> orientation{{cos(getOrientation()), -sin(getOrientation())}};


        std::array<double, MODEL_SPACE_DIMENSION> propulsion{{enginePush * orientation[X_DIM_VALUE] * time,
                                                                     enginePush * orientation[Y_DIM_VALUE] *
                                                                     time}}; // N / s


        const double speed = getSpeed();

        const double denominator =
                speed * sqrt(orientation[X_DIM_VALUE] * orientation[X_DIM_VALUE] + orientation[Y_DIM_VALUE] *
                                                                                   orientation[Y_DIM_VALUE]);

        const double numerator = fabs(orientation[X_DIM_VALUE] * getSpeedX() + orientation[Y_DIM_VALUE] * getSpeedY());

        const double angle = (denominator != 0.0)
                             ?
                             acos((denominator > numerator) ? numerator / denominator : 1.0)
                             : 0.0;

        const double dragValue =
                0.5 * SEA_M_VOL * DRAG_COEFFICIENT * SUBMERGED_SURFACE * exp(angle * M_PI) * speed;


        std::array<double, MODEL_SPACE_DIMENSION> drag{{-dragValue * getSpeedX(),
                                                               -dragValue * getSpeedY()}};

        std::array<double, MODEL_SPACE_DIMENSION> strengths{{propulsion[X_DIM_VALUE] + drag[X_DIM_VALUE],
                                                                    propulsion[Y_DIM_VALUE] + drag[Y_DIM_VALUE]}};


        std::array<double, MODEL_SPACE_DIMENSION> acceleration{{strengths[X_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT,
                                                                       strengths[Y_DIM_VALUE] /
                                                                       TITANIC_DEFAULT_WEIGHT}};


        setAccelerationX(acceleration[X_DIM_VALUE]);
        setAccelerationY(acceleration[Y_DIM_VALUE]);


        rudder.setWaterSpeedX(getSpeedX());
        rudder.setWaterSpeedY(getSpeedY());

        double rotationAcceleration = rudder.getRotationStrength() * 0.0;

        setRotationAcceleration(rotationAcceleration);

        PhysicObject2D::nextTime(time);
    }


    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }

    std::array<double, ENGINES_COUNTER> Titanic::getMachinesRotationSpeed() const {
        return std::array<double, ENGINES_COUNTER>{{engines[0]->getRotationSpeed(), engines[1]->getRotationSpeed(), engines[2]->getRotationSpeed()}};
    }
}