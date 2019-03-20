#include "Draftsman.h"

#define _USE_MATH_DEFINES


namespace model {

    PhysicObject2D::PhysicObject2D(const std::vector<std::array<double, 2>> &_points,
                                   double _xPosition,
                                   double _yPosition,
                                   double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                   double _xOrientation, double _yOrientation,
                                   double _weight) :
            ObjectND(_points, std::array<double, MODEL_SPACE_DIMENSION>{{_xPosition, _yPosition}},
                     std::array<double, MODEL_SPACE_DIMENSION>{{_xSpeed, _ySpeed}},
                     std::array<double, MODEL_SPACE_DIMENSION>{{_xAcceleration, _yAcceleration}},
                     std::array<double, MODEL_SPACE_DIMENSION>{{_xOrientation, _yOrientation}}, _weight) {
    }

    PhysicObject2D::PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                   double _xPosition,
                                   double _yPosition, double _xOrientation, double _yOrientation, double _weight)
            : PhysicObject2D(_points, _xPosition, _yPosition, DEFAULT_SPEED_X, DEFAULT_SPEED_Y, DEFAULT_ACCELERATION_X,
                             DEFAULT_ACCELERATION_Y, _xOrientation, _yOrientation, _weight) {
    }


    PhysicObject2D::PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                   double _weight) : PhysicObject2D(_points, DEFAULT_POSITION_X, DEFAULT_POSITION_Y,
                                                                    DEFAULT_ORIENTATION_X, DEFAULT_ORIENTATION_Y,
                                                                    _weight) {
    }


    PhysicObject2D::PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                   double _xPosition, double _yPosition, double _course, double _weight)
            : PhysicObject2D(_points, _xPosition, _yPosition, orientationConverterX(_course),
                             orientationConverterY(_course), _weight) {

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

    double PhysicObject2D::getOrientationX() const {
        return getOrientation(X_DIM_VALUE);
    }

    double PhysicObject2D::getOrientationY() const {
        return getOrientation(Y_DIM_VALUE);
    }

    void PhysicObject2D::setOrientationX(double value) {
        setOrientation(value, X_DIM_VALUE);
    }

    void PhysicObject2D::setOrientationY(double value) {
        setOrientation(value, Y_DIM_VALUE);
    }

    void PhysicObject2D::drawMe(view::Draftsman *draftsman) {
        draftsman->drawElement(this);
    }

    /* static functions */

    double PhysicObject2D::orientationConverterX(double course) {
        return cos(M_PI * course);
    }

    double PhysicObject2D::orientationConverterY(double course) {
        return sin(M_PI * course);
    }
}