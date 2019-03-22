
#include <iostream>
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::set<Point> Titanic::LIFT_COEFFICIENTS{{
                                                             {{0.0, 0.0}}
                                                     }};

    const std::set<Point> Titanic::DRAG_COEFFICIENTS{{
                                                             {{0.0, 0.1}}
                                                     }};


    const std::vector<Point> Titanic::DEFAULT_POINTS{{
                                                             {{0.0, 0.0}},
                                                             {{30.0, -14.0}},
                                                             {{218.0, -14.0}},
                                                             {{269.0, 0.0}},
                                                             {{218.0, 14.0}},
                                                             {{30.0, 14.0}},
                                                             {{0.0, 0.0}}
                                                     }};

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

        Vector drag = computeDrag(time);  // N

        Vector lift = computeLift(time);   // N

        Vector strengths{{propulsion[X_DIM_VALUE] + drag[X_DIM_VALUE] + lift[X_DIM_VALUE],
                                 propulsion[Y_DIM_VALUE] + drag[Y_DIM_VALUE] + lift[Y_DIM_VALUE]}};


        Vector acceleration{{strengths[X_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT,
                                    strengths[Y_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT}};


        setAccelerationX(acceleration[X_DIM_VALUE]);
        setAccelerationY(acceleration[Y_DIM_VALUE]);


        Vector rudderWaterSpeed = pointRotation(inverseVector(speed), orientation);

        rudder.setWaterSpeedX(rudderWaterSpeed[X_DIM_VALUE]);
        rudder.setWaterSpeedY(rudderWaterSpeed[Y_DIM_VALUE]);

        /*
        double rotationAcceleration = rudder.computeHydrodynamicStrength() * 0.0;

        setRotationAcceleration(rotationAcceleration);
*/
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

        const double incidence = angleBetweenVector(inverseVector(speed), directionVector());

        const double dragValue =
                0.5 * SEA_M_VOL * REFERENCE_SURFACE * approximatedDragCoefficient(incidence) * getSpeed();


        Vector drag{{-dragValue * getSpeedX(), -dragValue * getSpeedY()}};

        return drag; // N
    }

    Vector Titanic::computeLift(double time) const {

        Vector direction = directionVector();

        double incidence = angleBetweenVector(speed, directionVector());


        double liftValue =
                0.5 * SEA_M_VOL * REFERENCE_SURFACE * approximatedLiftCoefficient(incidence) * getSpeed();


        Vector vector{{liftValue * getSpeedX(), liftValue * getSpeedY()}};

        const double rotation = M_PI / 2.0;

        Vector larboardLift = pointRotation(vector, rotation);

        Vector starboardLift = pointRotation(vector, -rotation);

        return (angleBetweenVector(direction, larboardLift) < angleBetweenVector(direction, starboardLift)
                ? larboardLift : starboardLift); // N
    }

    Vector Titanic::computePropulsion(double time) const {

        double enginePush = 0.0; // N
        for (auto &engine : engines) {
            engine->nexTime(time);
            enginePush += engine->getPropulsionStrength();
        }

        Vector direction = directionVector();

        return Vector{{enginePush * direction[X_DIM_VALUE] * time, enginePush * direction[Y_DIM_VALUE] * time}}; // N
    }

    double Titanic::approximatedDragCoefficient(double incidence) const {

        return 0.0;
    }

    double Titanic::approximatedLiftCoefficient(double incidence) const {

        return incidence * 0.01;
    }
}