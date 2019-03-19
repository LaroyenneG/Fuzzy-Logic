

#include "PhysicObject2D.h"

namespace model {

    PhysicObject2D::PhysicObject2D(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                   double _xPosition,
                                   double _yPosition,
                                   double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                   double _weight) :
            ObjectND(_points, std::array<double, MODEL_SPACE_DIMENSION>{{_xPosition, _yPosition}},
                     std::array<double, MODEL_SPACE_DIMENSION>{{_xSpeed, _ySpeed}},
                     std::array<double, MODEL_SPACE_DIMENSION>{{_xAcceleration, _yAcceleration}}, _weight) {
    }

    PhysicObject2D::PhysicObject2D(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &_points, double _weight)
            : PhysicObject2D(_points,
                             DEFAULT_POSITION_X,
                             DEFAULT_POSITION_Y,
                             DEFAULT_SPEED_X,
                             DEFAULT_SPEED_Y,
                             DEFAULT_ACCELERATION_X,
                             DEFAULT_ACCELERATION_Y,
                             _weight) {
    }

    double PhysicObject2D::getPositionX() const {
        return getPosition(0);
    }

    double PhysicObject2D::getPositionY() const {
        return getPosition(1);
    }

    void PhysicObject2D::setPositionX(double value) {
        setPosition(value, 0);
    }

    void PhysicObject2D::setPositionY(double value) {
        setPosition(value, 1);
    }

    void PhysicObject2D::setSpeedX(double value) {
        setSpeed(value, 0);
    }

    void PhysicObject2D::setSpeedY(double value) {
        setSpeed(value, 1);
    }

    double PhysicObject2D::getSpeedX() const {
        return getSpeed(0);
    }

    double PhysicObject2D::getSpeedY() const {
        return getSpeed(1);
    }

    double PhysicObject2D::getAccelerationX() const {
        return getAcceleration(0);
    }

    double PhysicObject2D::getAccelerationY() const {
        return getAcceleration(1);
    }

    void PhysicObject2D::setAccelerationX(double value) {
        setAcceleration(value, 0);
    }

    void PhysicObject2D::setAccelerationY(double value) {
        setAcceleration(value, 1);
    }
}