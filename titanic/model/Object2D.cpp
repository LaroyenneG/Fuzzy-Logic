

#include "Object2D.h"

namespace model {

    Object2D::Object2D(const std::set<std::array<double, SPACE_DIMENSION>> &_points, double _xPosition,
                       double _yPosition,
                       double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration, double _weight) :
            ObjectND(_points, nullptr, nullptr, nullptr, _weight) {
    }

    Object2D::Object2D(const std::set<std::array<double, SPACE_DIMENSION>> &_points, double _weight)
            : Object2D(_points,
                       DEFAULT_POSITION_X,
                       DEFAULT_POSITION_Y,
                       DEFAULT_SPEED_X,
                       DEFAULT_SPEED_Y,
                       DEFAULT_ACCELERATION_X,
                       DEFAULT_ACCELERATION_Y,
                       _weight) {
    }

    double Object2D::getPositionX() const {
        return getPosition(0);
    }

    double Object2D::getPositionY() const {
        return getPosition(1);
    }

    void Object2D::setPositionX(double value) {
        setPosition(value, 0);
    }

    void Object2D::setPositionY(double value) {
        setPosition(value, 1);
    }

    void Object2D::setSpeedX(double value) {
        setSpeed(value, 0);
    }

    void Object2D::setSpeedY(double value) {
        setSpeed(value, 1);
    }

    double Object2D::getSpeedX() const {
        return getSpeed(0);
    }

    double Object2D::getSpeedY() const {
        return getSpeed(1);
    }

    double Object2D::getAccelerationX() const {
        return getAcceleration(0);
    }

    double Object2D::getAccelerationY() const {
        return getAcceleration(1);
    }

    void Object2D::setAccelerationX(double value) {
        setAcceleration(value, 0);
    }

    void Object2D::setAccelerationY(double value) {
        setAcceleration(value, 1);
    }
}