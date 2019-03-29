#include <utility>


#include <iostream>
#include "Rudder.h"
#include "Titanic.h"

namespace model {

    Rudder::Rudder()
            : Rudder(PhysicObject2D::loadCoefficients(RUDDER_DEFAULT_LIFT_COEFFICIENTS_FILE), RUDDER_DEFAULT_VALUE,
                     RUDDER_DEFAULT_W_SPEED_X, RUDDER_DEFAULT_W_SPEED_Y,
                     RUDDER_DEFAULT_SIZE) {

    }

    Rudder::Rudder(std::map<double, double> _lift_coefficients, double _value, double _xWaterSpeed,
                   double _yWaterSpeed,
                   double _size)
            : lift_coefficients(std::move(_lift_coefficients)), value(_value), waterSpeed{{_xWaterSpeed, _yWaterSpeed}},
              size(_size) {

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

        Vector orientation{{cos(value), sin(value)}};

        const double incidence = PhysicObject2D::angleBetweenVector(waterSpeed, orientation);


        const double liftValue =
                0.5 * SEA_M_VOL * getReferenceSurface() * approximatedLiftCoefficient(incidence) * getWaterSpeed();


        Vector vector{{liftValue * waterSpeed[X_DIM_VALUE], liftValue * waterSpeed[Y_DIM_VALUE]}};

        const double rotation = M_PI / 2.0;

        Vector larboardLift = PhysicObject2D::pointRotation(vector, rotation);

        Vector starboardLift = PhysicObject2D::pointRotation(vector, -rotation);

        Vector lift = (PhysicObject2D::angleBetweenVector(orientation, larboardLift) <
                               PhysicObject2D::angleBetweenVector(orientation, starboardLift)
                       ? larboardLift : starboardLift); // N


        const double dragValue =
                0.5 * SEA_M_VOL * getReferenceSurface() * approximatedDragCoefficient(incidence) * getWaterSpeed();

        Vector drag{{-dragValue * waterSpeed[X_DIM_VALUE], -dragValue * waterSpeed[Y_DIM_VALUE]}};

        return Vector{{lift[X_DIM_VALUE] + drag[X_DIM_VALUE], lift[Y_DIM_VALUE] + drag[Y_DIM_VALUE]}};
    }

    double Rudder::getWaterSpeed() const {
        return PhysicObject2D::normVector(waterSpeed);
    }

    double Rudder::getReferenceSurface() const {
        return size * TITANIC_DRAUGHT;
    }

    double Rudder::approximatedLiftCoefficient(double incidence) const {
        return PhysicObject2D::estimateOrdinateValue(incidence, lift_coefficients);
    }

    double Rudder::approximatedDragCoefficient(double incidence) const {
        return PhysicObject2D::estimateOrdinateValue(incidence, lift_coefficients);
    }
}