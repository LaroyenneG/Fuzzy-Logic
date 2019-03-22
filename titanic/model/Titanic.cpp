
#include <iostream>
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::vector<Point> Titanic::DEFAULT_POINTS{{{{0.0, 0.0}},
                                                             {{30.0, -14.0}},
                                                             {{218.0, -14.0}},
                                                             {{269.0, 0.0}},
                                                             {{218.0, 14.0}},
                                                             {{30.0, 14.0}},
                                                             {{0.0, 0.0}}}};

    Titanic::Titanic(const std::vector<Point> &points, double _orientation,
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


        Vector propulsion = computePropulsion(time); // N

        Vector drag = computeDrag(time);

        Vector bearing = computeBearing(time);


        Vector strengths{{propulsion[X_DIM_VALUE] + drag[X_DIM_VALUE] + bearing[X_DIM_VALUE],
                                 propulsion[Y_DIM_VALUE] + drag[Y_DIM_VALUE] + bearing[Y_DIM_VALUE]}};


        Vector acceleration{{strengths[X_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT,
                                    strengths[Y_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT}};


        setAccelerationX(acceleration[X_DIM_VALUE]);
        setAccelerationY(acceleration[Y_DIM_VALUE]);


        Vector rudderWaterSpeed = pointRotation(speed, getOrientation());

        rudder.setWaterSpeedX(rudderWaterSpeed[X_DIM_VALUE]);
        rudder.setWaterSpeedY(rudderWaterSpeed[Y_DIM_VALUE]);

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

    Vector Titanic::computeDrag(double time) const {

        const double incidence = angleBetweenVector(speed, directionVector());


        const double dragValue =
                0.0 * SEA_M_VOL * DRAG_COEFFICIENT * SUBMERGED_SURFACE * incidence * exp(incidence * M_PI) *
                normVector(speed);


        Vector drag{{-dragValue * getSpeedX(), -dragValue * getSpeedY()}};

        return drag; // N
    }

    Vector Titanic::computeBearing(double time) const {

        double incidence = angleBetweenVector(inverseVector(speed), directionVector());

        std::cout << incidence << '\n';

        double bearingValue =
                0.5 * SEA_M_VOL * DRAG_COEFFICIENT * SUBMERGED_SURFACE * exp(incidence * M_PI) * getSpeed();

        Vector bearing{{bearingValue * getSpeedX(), bearingValue * getSpeedY()}};

        double rotation = (true) ? M_PI / 2.0 : M_PI / 2.0;

        return pointRotation(bearing, rotation);
    }

    Vector Titanic::computePropulsion(double time) const {

        double enginePush = 0.0; // N
        for (auto &engine : engines) {
            engine->nexTime(time);
            enginePush += engine->getPropulsionStrength();
        }

        Vector direction = inverseVector(directionVector());

        return Vector{{enginePush * direction[X_DIM_VALUE] * time, enginePush * direction[Y_DIM_VALUE] * time}}; // N
    }
}