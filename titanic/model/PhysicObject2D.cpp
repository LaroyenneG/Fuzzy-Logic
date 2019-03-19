

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

    PhysicObject2D::PhysicObject2D(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                   double _xPosition,
                                   double _yPosition, double _weight)
            : PhysicObject2D(_points, _xPosition, _yPosition, DEFAULT_SPEED_X, DEFAULT_SPEED_Y, DEFAULT_ACCELERATION_X,
                             DEFAULT_ACCELERATION_Y, _weight) {
    }

    double PhysicObject2D::getPositionX() const {
        return getPosition(X_DIM_VALUE);
    }

    double PhysicObject2D::getPositionY() const {
        return getPosition(Y_DIM_VALUE);
    }

    void PhysicObject2D::setPositionX(double value) {
        setPosition(value, X_DIM_VALUE);
    }

    void PhysicObject2D::setPositionY(double value) {
        setPosition(value, Y_DIM_VALUE);
    }

    void PhysicObject2D::setSpeedX(double value) {
        setSpeed(value, X_DIM_VALUE);
    }

    void PhysicObject2D::setSpeedY(double value) {
        setSpeed(value, Y_DIM_VALUE);
    }

    double PhysicObject2D::getSpeedX() const {
        return getSpeed(X_DIM_VALUE);
    }

    double PhysicObject2D::getSpeedY() const {
        return getSpeed(Y_DIM_VALUE);
    }

    double PhysicObject2D::getAccelerationX() const {
        return getAcceleration(X_DIM_VALUE);
    }

    double PhysicObject2D::getAccelerationY() const {
        return getAcceleration(Y_DIM_VALUE);
    }

    void PhysicObject2D::setAccelerationX(double value) {
        setAcceleration(value, X_DIM_VALUE);
    }

    void PhysicObject2D::setAccelerationY(double value) {
        setAcceleration(value, Y_DIM_VALUE);
    }
}