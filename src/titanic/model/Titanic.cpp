#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"
#include "Draftsman.h"

#define _USE_MATH_DEFINES

#include <math.h>

namespace model {

    Titanic::Titanic(const std::vector<Point> &points, double _orientation, double _weight, double _xPosition,
                     double _yPosition, std::map<double, double> _lift_coefficients,
                     std::map<double, double> _drag_coefficients)
            : PhysicObject2D(points, _xPosition, _yPosition, _orientation, _weight),
              lift_coefficients(std::move(_lift_coefficients)), drag_coefficients(std::move(_drag_coefficients)),
              engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {
    }

    Titanic::Titanic() : Titanic(TITANIC_DEFAULT_X, TITANIC_DEFAULT_Y, TITANIC_DEFAULT_COURSE) {
    }

    Titanic::Titanic(double x, double y, double _orientation)
            : Titanic(loadShapePoints(TITANIC_DEFAULT_POINTS_FILE_NAME), _orientation, TITANIC_DEFAULT_WEIGHT, x, y,
                      loadCoefficients(TITANIC_DEFAULT_LIFT_COEFFICIENTS_FILE_NAME),
                      loadCoefficients(TITANIC_DEFAULT_DRAG_COEFFICIENTS_FILE_NAME)) {

    }

    void Titanic::resetToDefault() {

        PhysicObject2D::resetToDefault();

        setPositionX(TITANIC_DEFAULT_X);
        setPositionY(TITANIC_DEFAULT_Y);

        setWeight(TITANIC_DEFAULT_WEIGHT);
        setOrientation(TITANIC_DEFAULT_COURSE);

        for (auto engine : engines) {
            engine->resetToDefault();
        }

        rudder.resetToDefault();
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


#ifdef _ACTIVE_BLACK_BOX_
        {
            /* engines */

            unsigned int i = 0;
            for (auto engine : engines) {

                std::string engineLabel;
                engineLabel.append("engine ");
                engineLabel.append(std::to_string(i++));
                engineLabel.append(" ");

                blackBox.collectData(engineLabel + "(rotation speed)", engine->getRotationSpeed());
                blackBox.collectData(engineLabel + "(power)", engine->getPower());
                blackBox.collectData(engineLabel + "(propulsion)", engine->computePropulsionStrength());
            }

            /* incidence */

            blackBox.collectData("ship incidence", computeIncidence());

            /* lift */

            Vector lift = computeLift();

            blackBox.collectData("lift (x)", lift[X_DIM_VALUE]);
            blackBox.collectData("lift (y)", lift[Y_DIM_VALUE]);
            blackBox.collectData("lift", normVector(lift));
            blackBox.collectData("lift coefficient", approximatedLiftCoefficient(computeIncidence()));

            /* drag */

            Vector drag = computeDrag();

            blackBox.collectData("drag (x)", drag[X_DIM_VALUE]);
            blackBox.collectData("drag (y)", drag[Y_DIM_VALUE]);
            blackBox.collectData("drag", normVector(drag));
            blackBox.collectData("drag coefficient", approximatedDragCoefficient(computeIncidence()));

            /* centrifugal */

            Vector centrifugal = computeCentrifugalStrength();

            blackBox.collectData("centrifugal (x)", centrifugal[X_DIM_VALUE]);
            blackBox.collectData("centrifugal (y)", centrifugal[Y_DIM_VALUE]);
            blackBox.collectData("centrifugal", normVector(centrifugal));

            /* rudder */

            Vector rudderStrength = rudder.computeHydrodynamicStrength();

            blackBox.collectData("rudder value", rudder.getValue());
            blackBox.collectData("rudder strength (x)", rudderStrength[X_DIM_VALUE]);
            blackBox.collectData("rudder strength (y)", rudderStrength[Y_DIM_VALUE]);
            blackBox.collectData("rudder strength", normVector(rudderStrength));
            blackBox.collectData("rudder incidence", rudder.computeIncidence());
            blackBox.collectData("rudder lift coefficient",
                                 rudder.approximatedLiftCoefficient(rudder.computeIncidence()));
            blackBox.collectData("rudder drag coefficient",
                                 rudder.approximatedDragCoefficient(rudder.computeIncidence()));

            /* rotation friction */

            double rotationFriction = computeRotationFriction();

            blackBox.collectData("rotation friction", rotationFriction);
        }
#endif
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

        const double incidence = computeIncidence();

        const double dragValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedDragCoefficient(incidence) * getSpeed();


        Vector drag{{-dragValue * getSpeedX(), -dragValue * getSpeedY()}};

        return drag; // N
    }

    Vector Titanic::computeLift() const {

        const static double ROTATION = M_PI / 2.0;

        Vector direction = directionVector();

        const double incidence = computeIncidence();

        const double liftValue =
                0.5 * SEA_M_VOL * TITANIC_REFERENCE_SURFACE * approximatedLiftCoefficient(incidence) * getSpeed();


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
    }

    const LasersSensors<TITANIC_LASERS_COUNTER> &Titanic::getLasersSensors() const {

        return lasersSensors;
    }

    void Titanic::nextTimeRotation() {

        Vector direction = directionVector();

        Vector rudderStrength = computeRudder();

        const double torque = normVector(rudderStrength) * sin(angleBetweenVector(direction, rudderStrength)) *
                              TITANIC_DISTANCE_BETWEEN_RUDDER_AND_GRAVITY_CENTER;  // N*m

        const double rotationFriction = computeRotationFriction();

        const double angleAcceleration = (angleVectorDirection(rudderStrength, direction) *
                                          torque / TITANIC_MOMENT_OF_INERTIA) + rotationFriction; // radian / s²

        setRotationAcceleration(angleAcceleration);
    }

    void Titanic::nextTimeLinear() {

        Vector centrifugalForce = computeCentrifugalStrength(); // N
        Vector propulsion = computePropulsion(); // N
        Vector lift = computeLift(); // N
        Vector drag = computeDrag(); // N


        Vector strengthsSum{{propulsion[X_DIM_VALUE] + drag[X_DIM_VALUE] + lift[X_DIM_VALUE] +
                             centrifugalForce[X_DIM_VALUE],
                                    propulsion[Y_DIM_VALUE] + drag[Y_DIM_VALUE] + lift[Y_DIM_VALUE] +
                                    centrifugalForce[Y_DIM_VALUE]}};


        Vector acceleration{{strengthsSum[X_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT,
                                    strengthsSum[Y_DIM_VALUE] / TITANIC_DEFAULT_WEIGHT}};

        setAccelerationX(acceleration[X_DIM_VALUE]);
        setAccelerationY(acceleration[Y_DIM_VALUE]);
    }


    double Titanic::computeIncidence() const {

        return angleBetweenVector(speed, directionVector());
    }

    double Titanic::computeRotationFriction() const {

        static const double MOMENT_OF_INERTIA = TITANIC_MOMENT_OF_INERTIA;
        static const double DRAG_COEFFICIENT = 1.1;
        static const double DRAUGHT = TITANIC_DRAUGHT;
        static const double LENGTH = TITANIC_SIZE / 2.0;
        static const unsigned int SAMPLING = 10000;
        static const double STEP = LENGTH / SAMPLING;

        const double rotationSpeed = getRotationSpeed();
        const double direction = (rotationSpeed < 0) ? 1.0 : -1.0;

        double torque = 0.0;
        double a = 0.0;
        double b = STEP;

        for (unsigned int i = 0; i < 2; i++) {

            while (b < LENGTH) {

                double length = (a + b) / 2.0;

                double waterSpeed = rotationSpeed * length;

                double surface = (b - a) * DRAUGHT;

                double dragValue = 0.5 * SEA_M_VOL * surface * DRAG_COEFFICIENT * waterSpeed * waterSpeed;

                torque += dragValue * length / MOMENT_OF_INERTIA;

                a = b;
                b += STEP;
            }
        }

        return torque * direction;
    }

    void Titanic::reachMachinePower(double value) {

        for (auto engine : engines) {
            engine->reachPower(value);
        }
    }
}