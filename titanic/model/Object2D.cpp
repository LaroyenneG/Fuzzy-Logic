

#include "Object2D.h"

namespace model {

    Object2D::Object2D(const std::set<std::pair<double, double >> &_points, double _xPosition, double _yPosition,
                       double _xSpeed,
                       double _ySpeed, double _xAcceleration, double _yAcceleration, double _direction, double _weight)
            : points(_points), position{_xPosition, _yPosition}, speed{_xSpeed, _ySpeed},
              acceleration{_xAcceleration, _yAcceleration}, direction(_direction),
              weight(_weight) {
    }

    Object2D::Object2D(const std::set<std::pair<double, double >> &_points)
            : Object2D(_points,
                       DEFAULT_POSITION_X,
                       DEFAULT_POSITION_Y,
                       DEFAULT_SPEED_X,
                       DEFAULT_SPEED_Y,
                       DEFAULT_ACCELERATION_X,
                       DEFAULT_ACCELERATION_Y,
                       DEFAULT_DIRECTION,
                       DEFAULT_WEIGHT) {
    }

    Object2D::Object2D(const Object2D &object) {

        if (this != &object) {

            points = object.points;

            position[0] = object.position[0];
            position[1] = object.position[1];

            speed[0] = object.speed[0];
            speed[1] = object.speed[1];

            acceleration[0] = object.acceleration[0];
            acceleration[1] = object.acceleration[1];

            direction = object.direction;

            weight = object.weight;
        }
    }

    bool model::Object2D::touch(const Object2D &object) {
        return false;
    }

    double Object2D::getPositionX() const {
        return position[0];
    }

    double Object2D::getPositionY() const {
        return position[1];
    }

    void Object2D::setPositionX(double value) {
        position[0] = value;
    }

    void Object2D::setPositionY(double value) {
        position[1] = value;
    }

    double Object2D::getWeight() const {
        return weight;
    }

    void Object2D::setWeight(double value) {
        weight = value;
    }

    void Object2D::setSpeedX(double value) {
        speed[0] = value;
    }

    void Object2D::setSpeedY(double value) {
        speed[1] = value;
    }

    double Object2D::getSpeedX() const {
        return speed[0];
    }

    double Object2D::getSpeedY() const {
        return speed[1];
    }

    double Object2D::getDirection() const {
        return direction;
    }

    void Object2D::setDirection(double value) {
        direction = value;
    }

    void Object2D::nextPosition(double time) {

    }

    double Object2D::getAccelerationX() const {
        return acceleration[0];
    }

    double Object2D::getAccelerationY() const {
        return acceleration[1];
    }

    void Object2D::setAccelerationX(double value) {
        acceleration[0] = value;
    }

    void Object2D::setAccelerationY(double value) {
        acceleration[1] = value;
    }

    void Object2D::nextSpeed(double time) {

    }

    const std::set<std::pair<double, double >> &Object2D::getPoints() const {
        return points;
    }
}