#include "Draftsman.h"


namespace model {

    PhysicObject2D::PhysicObject2D(const std::vector<Point> &_points,
                                   double _xPosition,
                                   double _yPosition,
                                   double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                   double _orientation, double _rotationSpeed, double _rotationAcceleration,
                                   double _weight)
            : points(_points), position{{_xPosition, _yPosition}}, speed{{_xSpeed, _ySpeed}},
              acceleration{{_xAcceleration, _yAcceleration}}, orientation(_orientation), rotationSpeed(_rotationSpeed),
              rotationAcceleration(_rotationAcceleration), weight(_weight) {
    }

    PhysicObject2D::PhysicObject2D(const std::vector<Point> &_points,
                                   double _xPosition,
                                   double _yPosition, double _orientation, double _weight) :
            PhysicObject2D(_points, _xPosition, _yPosition, DEFAULT_SPEED_X, DEFAULT_SPEED_Y, DEFAULT_ACCELERATION_X,
                           DEFAULT_ACCELERATION_Y, _orientation, DEFAULT_ROTATION_SPEED, DEFAULT_ROTATION_ACCELERATION,
                           _weight) {
    }


    double PhysicObject2D::getPositionX() const {
        return position[X_DIM_VALUE];
    }

    double PhysicObject2D::getPositionY() const {
        return position[Y_DIM_VALUE];
    }

    void PhysicObject2D::setPositionX(double value) {
        position[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setPositionY(double value) {
        position[Y_DIM_VALUE] = value;
    }

    void PhysicObject2D::setSpeedX(double value) {
        speed[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setSpeedY(double value) {
        speed[Y_DIM_VALUE] = value;
    }

    double PhysicObject2D::getSpeedX() const {
        return speed[X_DIM_VALUE];
    }

    double PhysicObject2D::getSpeedY() const {
        return speed[Y_DIM_VALUE];
    }

    double PhysicObject2D::getAccelerationX() const {
        return acceleration[X_DIM_VALUE];
    }

    double PhysicObject2D::getAccelerationY() const {
        return acceleration[Y_DIM_VALUE];
    }

    void PhysicObject2D::setAccelerationX(double value) {
        acceleration[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setAccelerationY(double value) {
        acceleration[Y_DIM_VALUE] = value;
    }

    void PhysicObject2D::drawMe(view::Draftsman *draftsman) {
        draftsman->drawElement(this);
    }

    bool PhysicObject2D::touch(const PhysicObject2D &object) const {

        std::vector<Point> e1;
        writeAbsolutePoints(e1);

        std::vector<Point> e2;
        object.writeAbsolutePoints(e2);

        /********************************************************************/

        for (unsigned int i = 0; i < e1.size() - 1; ++i) {

            Point &p11 = e1[i];
            Point &p12 = e1[i + 1];

            Point v1{{p12[X_DIM_VALUE] - p11[X_DIM_VALUE], p12[Y_DIM_VALUE] - p11[Y_DIM_VALUE]}};

            for (unsigned int j = 0; j < e2.size() - 1; ++j) {

                Point &p21 = e2[j];
                Point &p22 = e2[j + 1];

                Vector v2{{p22[X_DIM_VALUE] - p21[X_DIM_VALUE], p22[Y_DIM_VALUE] - p21[Y_DIM_VALUE]}};

                if (v1[X_DIM_VALUE] * v2[Y_DIM_VALUE] != v1[Y_DIM_VALUE] * v2[X_DIM_VALUE]) {

                    double a1 = (p12[Y_DIM_VALUE] - p11[Y_DIM_VALUE]) / (p12[X_DIM_VALUE] - p11[X_DIM_VALUE]);
                    double c2 = p11[Y_DIM_VALUE] - a1 * p11[X_DIM_VALUE];

                    double a2 = (p22[Y_DIM_VALUE] - p21[Y_DIM_VALUE]) / (p22[X_DIM_VALUE] - p21[X_DIM_VALUE]);
                    double c1 = p21[Y_DIM_VALUE] - a2 * p21[X_DIM_VALUE];

                    double solution = (c1 - c2) / (a1 - a2);

                    if (MIN_VALUE(p11[X_DIM_VALUE], p12[X_DIM_VALUE]) < solution &&
                        MAX_VALUE(p11[X_DIM_VALUE], p12[X_DIM_VALUE]) > solution &&
                        MIN_VALUE(p21[X_DIM_VALUE], p22[X_DIM_VALUE]) < solution &&
                        MAX_VALUE(p21[X_DIM_VALUE], p22[X_DIM_VALUE]) > solution) {

                        return true;
                    }
                }
            }
        }

        return false;
    }

    void PhysicObject2D::writeAbsolutePoints(std::vector<Point> &points) const {

        for (auto &point : getPoints()) {

            Point nPoint = pointTranslation(pointRotation(point, orientation), position);

            points.push_back(nPoint);
        }
    }

    const std::vector<Point> &PhysicObject2D::getPoints() const {
        return points;
    }

    void PhysicObject2D::setOrientation(double value) {
        orientation = value;
    }

    double PhysicObject2D::getOrientation() const {
        return orientation;
    }

    double PhysicObject2D::getSpeed() const {
        return normVector(speed);
    }


    double PhysicObject2D::getRotationSpeed() const {
        return rotationSpeed;
    }

    double PhysicObject2D::getRotationAcceleration() const {
        return rotationAcceleration;
    }

    void PhysicObject2D::setRotationSpeed(double value) {
        rotationSpeed = value;
    }

    void PhysicObject2D::setRotationAcceleration(double value) {
        rotationAcceleration = value;
    }

    double PhysicObject2D::getWeight() const {
        return weight;
    }

    void PhysicObject2D::setWeight(double value) {
        weight = value;
    }

    void PhysicObject2D::nextTime(double time) {
        nextPosition(time);
        nextOrientation(time);
    }

    void PhysicObject2D::nextOrientation(double time) {
        rotationSpeed += rotationAcceleration * time;
        orientation += rotationSpeed * time;
    }

    void PhysicObject2D::nextPosition(double time) {

        speed[X_DIM_VALUE] += acceleration[X_DIM_VALUE] * time;
        speed[Y_DIM_VALUE] += acceleration[Y_DIM_VALUE] * time;

        position[X_DIM_VALUE] += speed[X_DIM_VALUE] * time;
        position[Y_DIM_VALUE] += speed[Y_DIM_VALUE] * time;
    }

    double PhysicObject2D::angleBetweenVector(const Vector &v1, const Vector &v2) {

        const double denominator = normVector(v1) * normVector(v2);

        const double numerator = v1[X_DIM_VALUE] * v2[X_DIM_VALUE] + v1[Y_DIM_VALUE] * v2[Y_DIM_VALUE];

        double relation = (denominator != 0.0) ? numerator / denominator : 0.0;

        if (relation >= 1.0) {
            relation = 1.0;
        }
        if (relation <= -1.0) {
            relation = -1.0;
        }

        return acos(relation);
    }

    double PhysicObject2D::normVector(const Vector &vector) {
        return sqrt(vector[X_DIM_VALUE] * vector[X_DIM_VALUE] + vector[Y_DIM_VALUE] * vector[Y_DIM_VALUE]);
    }

    Point PhysicObject2D::pointRotation(const Point &point, double angle) {

        Point nPoint;

        nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] * cos(angle) + point[Y_DIM_VALUE] * sin(angle);
        nPoint[Y_DIM_VALUE] = -point[X_DIM_VALUE] * sin(angle) + point[Y_DIM_VALUE] * cos(angle);

        return nPoint;
    }

    Point PhysicObject2D::pointTranslation(const Point &point, const Vector &translation) {

        Point nPoint;

        nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] + translation[X_DIM_VALUE];
        nPoint[Y_DIM_VALUE] = point[Y_DIM_VALUE] + translation[Y_DIM_VALUE];

        return nPoint;
    }

    Vector PhysicObject2D::directionVector() const {
        return Vector{{cos(orientation), sin(orientation)}};
    }

    Vector PhysicObject2D::inverseVector(const Vector &vector) {

        return Vector{{-vector[X_DIM_VALUE], -vector[Y_DIM_VALUE]}};
    }
}