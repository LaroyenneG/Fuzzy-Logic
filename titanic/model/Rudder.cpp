

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
        waterSpeed[0] = xValue;
    }

    void Rudder::setWaterSpeedY(double yValue) {
        waterSpeed[1] = yValue;
    }

    double Rudder::getRotationStrength() const {

        std::array<double, MODEL_SPACE_DIMENSION> orientation{{cos(value), -sin(value)}};


        const double normMultiply =
                getWaterSpeed() * sqrt(orientation[X_DIM_VALUE] * orientation[X_DIM_VALUE] + orientation[Y_DIM_VALUE] *
                                                                                             orientation[Y_DIM_VALUE]);

        const double angle = (normMultiply != 0.0) ? acos(
                (orientation[X_DIM_VALUE] * waterSpeed[0] + orientation[Y_DIM_VALUE] * waterSpeed[1]) / normMultiply)
                                                   : 0.0;

        return normMultiply * angle * size * RUDDER_MAGIC_NUMBER;
    }

    double Rudder::getWaterSpeed() const {
        return sqrt(waterSpeed[0] * waterSpeed[0] + waterSpeed[1] * waterSpeed[1]);
    }
}