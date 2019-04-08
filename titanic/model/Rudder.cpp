#include <utility>
#include <utility>
#include <iostream>
#include "Rudder.h"
#include "Titanic.h"

namespace model {

    Rudder::Rudder()
            : Rudder(PhysicObject2D::loadCoefficients(RUDDER_DEFAULT_LIFT_COEFFICIENTS_FILE),
                     PhysicObject2D::loadCoefficients(RUDDER_DEFAULT_DRAG_COEFFICIENTS_FILE), RUDDER_DEFAULT_VALUE,
                     RUDDER_DEFAULT_W_SPEED_X, RUDDER_DEFAULT_W_SPEED_Y,
                     RUDDER_DEFAULT_WIDTH, RUDDER_DEFAULT_HEIGHT, DEFAULT_ORIENTATION) {

    }

    Rudder::Rudder(std::map<double, double> _lift_coefficients, std::map<double, double> _drag_coefficients,
                   double _value, double _xWaterSpeed, double _yWaterSpeed, double _width, double _height,
                   double _orientation)
            : lift_coefficients(std::move(_lift_coefficients)), drag_coefficients(std::move(_drag_coefficients)),
              value(_value), orientation(_orientation),
              waterSpeed{{_xWaterSpeed, _yWaterSpeed}},
              width(_width), height(_height) {

    }

    void Rudder::setValue(double _value) {
        value = _value;
    }

    double Rudder::getValue() const {
        return value;
    }

    void Rudder::setWaterSpeedX(double xValue) {

        waterSpeed[X_DIM_VALUE] = xValue;
    }

    void Rudder::setWaterSpeedY(double yValue) {

        waterSpeed[Y_DIM_VALUE] = yValue;
    }

    Vector Rudder::computeHydrodynamicStrength() const {

        static const double ROTATION = M_PI / 2.0;

        Vector direction = directionVector();

        const double incidence = computeIncidence();

        const double liftValue =
                0.5 * SEA_M_VOL * getReferenceSurface() * approximatedLiftCoefficient(incidence) * getWaterSpeed();

        Vector vector{{liftValue * getWaterSpeedX(), liftValue * getWaterSpeedY()}};

        Vector larboardLift = PhysicObject2D::pointRotation(vector, ROTATION);

        Vector starboardLift = PhysicObject2D::pointRotation(vector, -ROTATION);

        Vector lift = (PhysicObject2D::angleBetweenVector(direction, larboardLift) <
                       PhysicObject2D::angleBetweenVector(direction, starboardLift)
                       ? larboardLift
                       : starboardLift); // N


        const double dragValue =
                0.5 * SEA_M_VOL * getReferenceSurface() * approximatedDragCoefficient(incidence) * getWaterSpeed();

        Vector drag{{-dragValue * getWaterSpeedX(), -dragValue * getWaterSpeedY()}};


        return Vector{{lift[X_DIM_VALUE] + drag[X_DIM_VALUE], lift[Y_DIM_VALUE] + drag[Y_DIM_VALUE]}};
    }

    void Rudder::setOrientation(double _orientation) {

        orientation = _orientation;
    }

    double Rudder::getWaterSpeed() const {

        return PhysicObject2D::normVector(waterSpeed);
    }

    double Rudder::getReferenceSurface() const {

        return width * height;
    }

    double Rudder::approximatedLiftCoefficient(double incidence) const {

        return PhysicObject2D::estimateOrdinateValue(incidence, lift_coefficients);
    }

    double Rudder::approximatedDragCoefficient(double incidence) const {

        return PhysicObject2D::estimateOrdinateValue(incidence, drag_coefficients);
    }

    Vector Rudder::directionVector() const {

        return Vector{{cos(value + orientation), sin(value + orientation)}};;
    }

    double Rudder::getWaterSpeedX() const {

        return waterSpeed[X_DIM_VALUE];
    }

    double Rudder::getWaterSpeedY() const {

        return waterSpeed[Y_DIM_VALUE];
    }

    double Rudder::computeIncidence() const {

        return PhysicObject2D::angleBetweenVector(waterSpeed, directionVector());
    }
}