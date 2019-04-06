
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"
#include "Draftsman.h"

namespace model {

    Titanic::Titanic(const std::vector<Point> &points, double _orientation, double _weight, double _xPosition,
                     double _yPosition, std::map<double, double> _lift_coefficients,
                     std::map<double, double> _drag_coefficients)
            : PhysicObject2D(points, _xPosition, _yPosition, _orientation, _weight),
              lift_coefficients(std::move(_lift_coefficients)), drag_coefficients(std::move(_drag_coefficients)),
              engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {

        setSpeedY(12.0);
    }

    Titanic::Titanic() : Titanic(TITANIC_DEFAULT_X, TITANIC_DEFAULT_Y, TITANIC_DEFAULT_COURSE) {
    }

    Titanic::Titanic(double x, double y, double _orientation)
            : Titanic(loadShapePoints(TITANIC_DEFAULT_POINTS_FILE_NAME), _orientation, TITANIC_DEFAULT_WEIGHT, x, y,
                      loadCoefficients(TITANIC_DEFAULT_LIFT_COEFFICIENTS_FILE_NAME),
                      loadCoefficients(TITANIC_DEFAULT_DRAG_COEFFICIENTS_FILE_NAME)) {

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

        const static Point LASERS_SENSORS_TRANSLATION{{TITANIC_LASERS_SENSORS_POSITION_X, TITANIC_LASERS_SENSORS_POSITION_Y}};

        for (auto engine : engines) {
            engine->nexTime(time);
        }


        nextTimeLinear();
        nextTimeRotation();

        PhysicObject2D::nextTime(time);

        Point lasersSensorsPosition = pointTranslation(pointRotation(LASERS_SENSORS_TRANSLATION, orientation),
                                                       position);

        lasersSensors.setPosition(lasersSensorsPosition);
        lasersSensors.setOrientation(orientation);
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


    Vector Titanic::computeRudder() {

        rudder.setOrientation(orientation);
        rudder.setWaterSpeedX(speed[X_DIM_VALUE]);
        rudder.setWaterSpeedY(speed[Y_DIM_VALUE]);

        return rudder.computeHydrodynamicStrength();
    }

    Vector Titanic::computeDrag() const {

        const double incidence = angleBetweenVector(speed, directionVector());

        const double dragValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedDragCoefficient(incidence) * getSpeed() *
                TITANIC_MAGIC_NUMBER;


        Vector drag{{-dragValue * getSpeedX(), -dragValue * getSpeedY()}};

        return drag; // N
    }

    Vector Titanic::computeLift() const {

        const static double ROTATION = M_PI / 2.0;

        Vector direction = directionVector();

        double incidence = angleBetweenVector(speed, direction);


        double liftValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedLiftCoefficient(incidence) * getSpeed() *
                TITANIC_MAGIC_NUMBER;


        Vector vector{{liftValue * getSpeedX(), liftValue * getSpeedY()}};

        Vector larboardLift = pointRotation(vector, ROTATION);

        Vector starboardLift = pointRotation(vector, -ROTATION);

        return (angleBetweenVector(direction, larboardLift) < angleBetweenVector(direction, starboardLift)
                ? larboardLift
                : starboardLift); // N
    }

    Vector Titanic::computePropulsion() const {

        double enginePush = 0.0; // N
        for (auto &engine : engines) {
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
        draftsman->drawElement(this);
    }

    const LasersSensors<TITANIC_LASERS_COUNTER> &Titanic::getLasersSensors() const {
        return lasersSensors;
    }

    void Titanic::nextTimeRotation() {

        Vector direction = directionVector();

        Vector rudderStrength = computeRudder();

        const double couple = normVector(rudderStrength) * sin(angleBetweenVector(direction, rudderStrength)) *
                              TITANIC_DISTANCE_BETWEEN_RUDDER_AND_GRAVITY_CENTER;  // N*m


        const double rotationFriction = -TITANIC_ROTATION_FRICTION * getRotationSpeed() /
                                        TITANIC_DEFAULT_WEIGHT;

        const double angleAcceleration = (angleVectorDirection(rudderStrength, direction) *
                                          couple / TITANIC_MOMENT_OF_INERTIA) + rotationFriction; // radian / s²

        setRotationAcceleration(angleAcceleration);
    }

    void Titanic::nextTimeLinear() {

        Vector centrifugalForce = computeCentrifugalForce(); // N
        Vector propulsion = computePropulsion(); // N
        Vector lift = computeLift(); // N
        Vector drag = computeDrag(); // N


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