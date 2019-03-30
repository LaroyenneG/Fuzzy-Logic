
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"
#include "Draftsman.h"

namespace model {

    Titanic::Titanic(const std::vector<Point> &points, double _orientation, double _weight, double _xPosition,
                     double _yPosition, std::map<double, double> _lift_coefficients,
                     std::map<double, double> _drag_coefficients, double _range, double _angle)
            : PhysicObject2D(points, _xPosition, _yPosition, _orientation, _weight),
              lift_coefficients(std::move(_lift_coefficients)), drag_coefficients(std::move(_drag_coefficients)),
              laserSensor(_xPosition, _yPosition, _orientation, _range, _angle),
              engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {
    }

    Titanic::Titanic() : Titanic(TITANIC_DEFAULT_X, TITANIC_DEFAULT_Y, TITANIC_DEFAULT_COURSE) {

    }

    Titanic::Titanic(double x, double y, double _orientation)
            : Titanic(loadShapePoints(TITANIC_DEFAULT_POINTS_FILE_NAME), _orientation, TITANIC_DEFAULT_WEIGHT, x, y,
                      loadCoefficients(TITANIC_DEFAULT_LIFT_COEFFICIENTS_FILE_NAME),
                      loadCoefficients(TITANIC_DEFAULT_DRAG_COEFFICIENTS_FILE_NAME), TITANIC_LASERS_RANGE,
                      TITANIC_LASERS_ANGLE) {

    }

    void Titanic::setRudderValue(double value) {
        rudder.setValue(value);
    }

    void Titanic::setMachinePower(double value) {

        engines[TITANIC_ALTERNATIVE_MACHINE_1_RANK]->setPower(value);
        engines[TITANIC_ALTERNATIVE_MACHINE_2_RANK]->setPower(value);
        engines[TITANIC_TURBINE_MACHINE_RANK]->setPower((value > 0.0) ? value : 0.0);
    }

    void Titanic::nextTime(double time) {

        std::thread linearThread([&] { nextTimeLinear(time); });
        std::thread rotationThread([&] { nextTimeRotation(time); });

        linearThread.join();
        rotationThread.join();

        PhysicObject2D::nextTime(time);

        laserSensor.setPosition(position);
    }


    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }

    std::array<double, TITANIC_ENGINES_COUNTER> Titanic::getMachinesRotationSpeed() const {

        return std::array<double, TITANIC_ENGINES_COUNTER>{{
                                                                   engines[TITANIC_ALTERNATIVE_MACHINE_1_RANK]->getRotationSpeed(),
                                                                   engines[TITANIC_ALTERNATIVE_MACHINE_2_RANK]->getRotationSpeed(),
                                                                   engines[TITANIC_TURBINE_MACHINE_RANK]->getRotationSpeed()
                                                           }};
    }


    Vector Titanic::computeRudder(double time) {

        Vector rudderWaterSpeed = pointRotation(inverseVector(speed), orientation);

        rudder.setWaterSpeedX(rudderWaterSpeed[X_DIM_VALUE]);
        rudder.setWaterSpeedY(rudderWaterSpeed[Y_DIM_VALUE]);

        return rudder.computeHydrodynamicStrength();
    }

    Vector Titanic::computeDrag(double time) const {

        const double incidence = angleBetweenVector(speed, directionVector());

        const double dragValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedDragCoefficient(incidence) * getSpeed();


        Vector drag{{-dragValue * getSpeedX(), -dragValue * getSpeedY()}};

        return drag; // N
    }

    Vector Titanic::computeLift(double time) const {

        Vector direction = directionVector();

        double incidence = angleBetweenVector(speed, direction);


        double liftValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedLiftCoefficient(incidence) * getSpeed();


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
            enginePush += engine->computePropulsionStrength();
        }

        Vector direction = directionVector();

        return Vector{{enginePush * direction[X_DIM_VALUE], enginePush * direction[Y_DIM_VALUE]}}; // N
    }

    double Titanic::approximatedDragCoefficient(double incidence) const {

        return estimateOrdinateValue(incidence, drag_coefficients);
    }

    double Titanic::approximatedLiftCoefficient(double incidence) const {

        return estimateOrdinateValue(incidence, lift_coefficients);
    }

    void Titanic::drawMe(view::Draftsman *draftsman) {
        draftsman->drawTitanic(this);
    }

    const LaserSensor<TITANIC_LASERS_COUNTER> &Titanic::getLaserSensor() const {
        return laserSensor;
    }

    void Titanic::nextTimeRotation(double time) {

        Vector rudderStrength = computeRudder(time);

        const double coupleDirection = (normVector(rudderStrength) != 0)
                                       ? rudderStrength[Y_DIM_VALUE] / fabs(rudderStrength[Y_DIM_VALUE])
                                       : 0.0;

        const double couple =
                fabs(normVector(rudderStrength) * sin(angleBetweenVector(directionVector(), rudderStrength)) *
                     TITANIC_DISTANCE_BETWEEN_RUDDER_AND_GRAVITY_CENTER) * coupleDirection;  // N.m

        const double angleAcceleration =
                (couple / TITANIC_MOMENT_OF_INERTIA -
                 TITANIC_ROTATION_FRICTION * getRotationSpeed() / TITANIC_DEFAULT_WEIGHT); // radian / s²

        setRotationAcceleration(angleAcceleration);
    }

    void Titanic::nextTimeLinear(double time) {

        Vector centrifugalForce; // N
        Vector propulsion; // N
        Vector drag;  // N
        Vector lift;   // N

        std::thread centrifugalThread([&] { centrifugalForce = computeCentrifugalForce(); });
        std::thread threadPropulsion([&] { propulsion = computePropulsion(time); });
        std::thread threadLift([&] { lift = computeLift(time); });
        std::thread threadDrag([&] { drag = computeDrag(time); });


        centrifugalThread.join();
        threadPropulsion.join();
        threadLift.join();
        threadDrag.join();


        Vector strengths{{propulsion[X_DIM_VALUE] + drag[X_DIM_VALUE] + lift[X_DIM_VALUE] +
                          centrifugalForce[X_DIM_VALUE],
                                 propulsion[Y_DIM_VALUE] + drag[Y_DIM_VALUE] + lift[Y_DIM_VALUE] +
                                 centrifugalForce[Y_DIM_VALUE]}};


        Vector acceleration{{strengths[X_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT,
                                    strengths[Y_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT}};

        setAccelerationX(acceleration[X_DIM_VALUE]);
        setAccelerationY(acceleration[Y_DIM_VALUE]);
    }
}