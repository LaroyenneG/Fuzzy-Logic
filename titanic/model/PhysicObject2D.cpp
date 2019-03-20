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

    bool PhysicObject2D::touch(const ObjectND<double, MODEL_SPACE_DIMENSION> &object) const {

        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> e1;
        writeAbsolutePoints(e1);

        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> e2;
        object.writeAbsolutePoints(e2);

        /********************************************************************/

        for (unsigned int i = 0; i < e1.size() - 1; ++i) {

            auto &p11 = e1[i];
            auto &p12 = e1[i + 1];

            std::array<double, MODEL_SPACE_DIMENSION> v1{{p12[X_DIM_VALUE] - p11[X_DIM_VALUE],
                                                                 p12[Y_DIM_VALUE] - p11[Y_DIM_VALUE]}};

            for (unsigned int j = 0; j < e2.size(); ++j) {

                auto &p21 = e2[j];
                auto &p22 = e2[j + 1];

                std::array<double, MODEL_SPACE_DIMENSION> v2{{p22[X_DIM_VALUE] - p21[X_DIM_VALUE],
                                                                     p22[Y_DIM_VALUE] - p21[Y_DIM_VALUE]}};

                if (v1[X_DIM_VALUE] * v2[Y_DIM_VALUE] != v1[Y_DIM_VALUE] * v2[X_DIM_VALUE]) {

                    double a1 = (p12[Y_DIM_VALUE] - p11[Y_DIM_VALUE]) / (p12[X_DIM_VALUE] - p11[X_DIM_VALUE]);
                    double c2 = p11[Y_DIM_VALUE] - a1 * p11[X_DIM_VALUE];

                    double a2 = (p22[Y_DIM_VALUE] - p21[Y_DIM_VALUE]) / (p22[X_DIM_VALUE] - p21[X_DIM_VALUE]);
                    double c1 = p21[Y_DIM_VALUE] - a2 * p21[X_DIM_VALUE];

                    double solution = (c1 - c2) / (a1 - a2);

                    if (MIN_VALUE(p11[X_DIM_VALUE], p12[X_DIM_VALUE]) > solution &&
                        MAX_VALUE(p11[X_DIM_VALUE], p12[X_DIM_VALUE]) < solution &&
                        MIN_VALUE(p21[X_DIM_VALUE], p22[X_DIM_VALUE]) > solution &&
                        MAX_VALUE(p21[X_DIM_VALUE], p22[X_DIM_VALUE]) < solution) {

                        return true;
                    }
                }
            }
        }

        return false;
    }

    void PhysicObject2D::writeAbsolutePoints(std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points) const {


        const double norm = sqrt(getOrientation(X_DIM_VALUE) * getOrientation(X_DIM_VALUE) +
                                 getOrientation(Y_DIM_VALUE) * getOrientation(Y_DIM_VALUE));

        const double xOrientation = (norm != 0.0) ? getOrientation(X_DIM_VALUE) / norm : 0.0;
        const double yOrientation = (norm != 0.0) ? getOrientation(Y_DIM_VALUE) / norm : 0.0;

        for (auto &point : getPoints()) {

            std::array<double, MODEL_SPACE_DIMENSION> nPoint = point;

            nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] * xOrientation + point[Y_DIM_VALUE] * yOrientation +
                                  getPosition(X_DIM_VALUE);
            nPoint[Y_DIM_VALUE] = -point[X_DIM_VALUE] * yOrientation + point[Y_DIM_VALUE] * xOrientation +
                                  getPosition(Y_DIM_VALUE);

            points.push_back(nPoint);
        }
    }
}