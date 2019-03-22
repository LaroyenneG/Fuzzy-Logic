

#include <iostream>
#include "Rudder.h"

namespace model {

    Rudder::Rudder()
            : Rudder(RUDDER_DEFAULT_VALUE, RUDDER_DEFAULT_W_SPEED_X, RUDDER_DEFAULT_W_SPEED_Y, RUDDER_DEFAULT_SIZE) {

    }

    Rudder::Rudder(double _value, double _xWaterSpeed, double _yWaterSpeed, double _size)
            : value(_value), waterSpeed{{_xWaterSpeed, _yWaterSpeed}}, size(_size) {

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

    double Rudder::getRotationStrength() const {

        Vector orientation{{cos(value), sin(value)}};

        const double angle = PhysicObject2D::angleBetweenVector(waterSpeed, orientation);

        return angle * size * RUDDER_MAGIC_NUMBER * getWaterSpeed();
    }

    double Rudder::getWaterSpeed() const {
        return PhysicObject2D::normVector(waterSpeed);
    }
}