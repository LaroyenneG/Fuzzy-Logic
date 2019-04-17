#include "PhysicObject2D.h"
#include "Draftsman.h"

#define _USE_MATH_DEFINES

#include <pso/FitnessEvaluatorInterface.h>
#include <pso/ParticleSwarmOptimization.h>
#include <math.h>

namespace model {

    PhysicObject2D::PhysicObject2D(std::vector<Point> _points,
                                   double _xPosition, double _yPosition, double _xSpeed, double _ySpeed,
                                   double _xAcceleration, double _yAcceleration,
                                   double _orientation, double _rotationSpeed, double _rotationAcceleration,
                                   double _weight)
            : points(std::move(_points)), position{{_xPosition, _yPosition}}, speed{{_xSpeed, _ySpeed}},
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

#ifdef _ACTIVE_BLACK_BOX_

    const BlackBox &PhysicObject2D::getBlackBox() const {
        return blackBox;
    }

#endif

    void PhysicObject2D::resetToDefault() {

        setOrientation(DEFAULT_ORIENTATION);

        setPositionX(DEFAULT_POSITION_X);
        setPositionY(DEFAULT_POSITION_Y);

        setSpeedX(DEFAULT_SPEED_X);
        setSpeedY(DEFAULT_SPEED_Y);

        setAccelerationX(DEFAULT_ACCELERATION_X);
        setAccelerationY(DEFAULT_ACCELERATION_Y);

        setRotationSpeed(DEFAULT_ROTATION_SPEED);
        setRotationAcceleration(DEFAULT_ROTATION_ACCELERATION);
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

    double PhysicObject2D::distance(const PhysicObject2D &object) const {

        std::vector<Point> myPoints;
        writeAbsolutePoints(myPoints);

        std::vector<Point> objectPoints;
        object.writeAbsolutePoints(objectPoints);

        double bestDistance = INFINITY;

        for (auto myPoint : myPoints) {

            for (auto objectPoint : objectPoints) {

                double distance = distanceBetweenPoint(myPoint, objectPoint);

                if (bestDistance > distance) {
                    bestDistance = distance;
                }
            }
        }

        return bestDistance;
    }

    bool PhysicObject2D::touch(const PhysicObject2D &object) const {

        std::vector<Point> shape1;
        writeAbsolutePoints(shape1);

        std::vector<Point> shape2;
        object.writeAbsolutePoints(shape2);


        for (unsigned int i = 0; !shape1.empty() && i < shape1.size() - 1; ++i) {

            Line line1 = constructLine(shape1[i], shape1[i + 1]);

            for (unsigned int j = 0; !shape2.empty() && j < shape2.size() - 1; ++j) {

                Line line2 = constructLine(shape2[j], shape2[j + 1]);

                bool status = false; // if true then intersection in segments

                findLineIntersection(line1, line2, &status);

                if (status) {
                    return true;
                }
            }
        }

        return false;
    }

    Vector PhysicObject2D::computeCentrifugalStrength() const {

        static const double NEGLIGIBLE = pow(10, -9);

        Vector strength{{0.0, 0.0}};

        if (positions.size() == POINT_QUEUE_SIZE) {

            Point positionArray[POINT_QUEUE_SIZE];

            int index = 0;
            for (auto it = positions.begin(); it != positions.end(); it++, index++) {
                positionArray[index] = *it;
            }

            Vector dv1{{positionArray[1][X_DIM_VALUE] - positionArray[0][X_DIM_VALUE],
                               positionArray[1][Y_DIM_VALUE] - positionArray[0][Y_DIM_VALUE]}};
            Vector dv2{{positionArray[2][X_DIM_VALUE] - positionArray[0][X_DIM_VALUE],
                               positionArray[2][Y_DIM_VALUE] - positionArray[0][Y_DIM_VALUE]}};

            double angleAlign = angleBetweenVector(dv1, dv2);

            if (angleAlign >= NEGLIGIBLE) {

                Point circleCenter = circleCenterSolver(positionArray[0], positionArray[1], positionArray[2]);

                double rayon = distanceBetweenPoint(circleCenter, positionArray[0]);

                Vector direction = vectorBetweenPoints(circleCenter, positionArray[0]);

                double directionNorm = normVector(direction);

                direction[X_DIM_VALUE] /= directionNorm;
                direction[Y_DIM_VALUE] /= directionNorm;

                double value = weight * getSpeed() / rayon;

                strength = {value * direction[X_DIM_VALUE], value * direction[Y_DIM_VALUE]};
            }
        }

        return strength;
    }

    void PhysicObject2D::writeAbsolutePoints(std::vector<Point> &wPoints) const {

        for (auto &point : getPoints()) {

            wPoints.push_back(pointTranslation(pointRotation(point, orientation), position));
        }
    }

    const std::vector<Point> &PhysicObject2D::getPoints() const {

        return points;
    }

    void PhysicObject2D::setOrientation(double value) {

        orientation = value;
    }

    double PhysicObject2D::getAcceleration() const {

        return normVector(acceleration);
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

        nextRotationSpeed(time);
        nextOrientation(time);

        nextSpeed(time);
        nextPosition(time);

#ifdef _ACTIVE_BLACK_BOX_
        {
            /* weight */

            blackBox.collectData("weight", getWeight());

            /* position */

            blackBox.collectData("position (x)", getPositionX());
            blackBox.collectData("position (y)", getPositionY());

            /* speed */

            blackBox.collectData("speed (x)", getSpeedX());
            blackBox.collectData("speed (y)", getSpeedY());

            blackBox.collectData("speed", getSpeed());

            /* acceleration */

            blackBox.collectData("acceleration (x)", getAccelerationX());
            blackBox.collectData("acceleration (y)", getAccelerationY());

            blackBox.collectData("acceleration", getAcceleration());

            /* rotation */

            blackBox.collectData("orientation", getOrientation());

            /* rotation speed */

            blackBox.collectData("rotation speed", getRotationSpeed());

            /* rotation acceleration */

            blackBox.collectData("rotation acceleration", getRotationAcceleration());

            /* points */

            unsigned int i = 0;
            for (auto p : positions) {

                std::string pointLabel;
                pointLabel.append("point ");
                pointLabel.append(std::to_string(i++));
                pointLabel.append(" ");

                blackBox.collectData(pointLabel + "(x)", p[X_DIM_VALUE]);
                blackBox.collectData(pointLabel + "(y)", p[Y_DIM_VALUE]);
            }
        }
#endif
    }

    void PhysicObject2D::nextSpeed(double time) {

        speed[X_DIM_VALUE] += acceleration[X_DIM_VALUE] * time;
        speed[Y_DIM_VALUE] += acceleration[Y_DIM_VALUE] * time;
    }

    void PhysicObject2D::nextRotationSpeed(double time) {

        rotationSpeed += rotationAcceleration * time;
    }

    void PhysicObject2D::nextOrientation(double time) {

        orientation += rotationSpeed * time;
    }

    void PhysicObject2D::nextPosition(double time) {

        position[X_DIM_VALUE] += speed[X_DIM_VALUE] * time;
        position[Y_DIM_VALUE] += speed[Y_DIM_VALUE] * time;

        if (positions.size() >= POINT_QUEUE_SIZE) {
            positions.pop_front();
        }

        positions.push_back(position);
    }

    double PhysicObject2D::angleBetweenVector(const Vector &vector1, const Vector &vector2) {

        const double denominator = normVector(vector1) * normVector(vector2);

        const double numerator =
                vector1[X_DIM_VALUE] * vector2[X_DIM_VALUE] + vector1[Y_DIM_VALUE] * vector2[Y_DIM_VALUE];

        double relation = (denominator != 0.0) ? numerator / denominator : M_PI / 2.0;

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

        return Point{{point[X_DIM_VALUE] * cos(angle) - point[Y_DIM_VALUE] * sin(angle),
                             point[X_DIM_VALUE] * sin(angle) + point[Y_DIM_VALUE] * cos(angle)}};
    }

    Point PhysicObject2D::pointTranslation(const Point &point, const Vector &translation) {

        return Point{{point[X_DIM_VALUE] + translation[X_DIM_VALUE], point[Y_DIM_VALUE] + translation[Y_DIM_VALUE]}};
    }

    Vector PhysicObject2D::directionVector() const {

        return Vector{{cos(orientation), sin(orientation)}};
    }

    Vector PhysicObject2D::inverseVector(const Vector &vector) {

        return Vector{{-vector[X_DIM_VALUE], -vector[Y_DIM_VALUE]}};
    }

    std::vector<Point> PhysicObject2D::loadShapePoints(const std::string &filePath) {

        static const double POINT_MAX_VALUE = INFINITY;

        std::vector<Point> points;

        std::ifstream ifstream(filePath);

        while (ifstream) {

            double x = POINT_MAX_VALUE;
            double y = POINT_MAX_VALUE;

            ifstream >> x;
            ifstream >> y;

            if (x != POINT_MAX_VALUE && y != POINT_MAX_VALUE) {
                points.push_back(Point{{x, y}});
            }
        }

        ifstream.close();

        return points;
    }

    double PhysicObject2D::distanceBetweenPoint(const Point &point1, const Point &point2) {

        double somme = 0.0;

        for (unsigned int i = 0; i < MODEL_SPACE_DIMENSION; ++i) {
            somme += (point1[i] - point2[i]) * (point1[i] - point2[i]);
        }

        return std::sqrt(somme);
    }

    Point PhysicObject2D::circleCenterSolver(const Point &p1, const Point &p2, const Point &p3) {

        static const double MAX_RAYON = 10000;

        class CenterCircleFitness : public FitnessEvaluatorInterface {

        private:
            const Point &p1;
            const Point &p2;
            const Point &p3;

        public:
            explicit CenterCircleFitness(const Point &_p1, const Point &_p2, const Point &_p3)
                    : p1(_p1), p2(_p2), p3(_p3) {

            }

            double computeFitness(double *particlePosition, unsigned int dimension) const override {

                if (dimension != MODEL_SPACE_DIMENSION) {
                    std::cerr << "Invalid dimension for circle center solver" << std::endl;
                    exit(EXIT_FAILURE);
                }

                Point center{{particlePosition[X_DIM_VALUE], particlePosition[Y_DIM_VALUE]}};

                double d1 = distanceBetweenPoint(center, p1);
                double d2 = distanceBetweenPoint(center, p2);
                double d3 = distanceBetweenPoint(center, p3);

                return fabs(d1 - d2) + fabs(d2 - d3) + fabs(d1 - d3);
            }
        };

        Point center{{INFINITY, INFINITY}};

        CenterCircleFitness centerCircleFitness(p1, p2, p3);

        ParticleSwarmOptimization pso(MODEL_SPACE_DIMENSION, 100, 10, 1000, -4.0, 4.0, 0,
                                      MIN_VALUE(p2[X_DIM_VALUE], p2[Y_DIM_VALUE]) - MAX_RAYON,
                                      MAX_VALUE(p2[X_DIM_VALUE], p2[Y_DIM_VALUE]) + MAX_RAYON, 2, 2, 0.0,
                                      &centerCircleFitness);

        Particle *particle = pso.processing();

        if (particle != nullptr) {
            center[X_DIM_VALUE] = particle->getBestPosition(X_DIM_VALUE);
            center[Y_DIM_VALUE] = particle->getBestPosition(Y_DIM_VALUE);
        }

        return center;
    }

    Vector PhysicObject2D::vectorBetweenPoints(const Point &point1, const Point &point2) {

        return Vector{{point2[X_DIM_VALUE] - point1[X_DIM_VALUE], point2[Y_DIM_VALUE] - point1[Y_DIM_VALUE]}};
    }


    double PhysicObject2D::estimateOrdinateValue(double abscissa, const std::map<double, double> &points) {

        std::list<std::pair<double, double>> sortedPoints;

        for (auto &point : points) {
            sortedPoints.push_front(point);
        }

        sortedPoints.sort([](const std::pair<double, double> &p1, const std::pair<double, double> &p2) {
            return p1.first < p2.first;
        });

        double value = INFINITY;

        if (sortedPoints.size() >= 2) {

            std::pair<double, double> leftPoint;

            bool initLeft = false;

            for (auto it = sortedPoints.begin(); it != sortedPoints.end(); it++) {

                std::pair<double, double> point = *it;

                if (!initLeft) {
                    leftPoint = point;
                    initLeft = true;
                }

                if (leftPoint.first < point.first && point.first <= abscissa) {
                    leftPoint = point;
                }
            }


            std::pair<double, double> rightPoint;

            bool initRight = false;

            for (auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); it++) {

                std::pair<double, double> point = *it;

                if (!initRight) {
                    rightPoint = point;
                    initRight = true;
                }

                if (rightPoint.first > point.first && point.first >= abscissa) {
                    rightPoint = point;
                }
            }

            if (initRight && initLeft) {

                if (leftPoint == rightPoint) {

                    value = leftPoint.second;

                } else if (leftPoint.first != rightPoint.first) {

                    // equation : y = a*x+b

                    const double a = (rightPoint.second - leftPoint.second) / (rightPoint.first - leftPoint.first);

                    const double b = leftPoint.second - a * leftPoint.first;

                    value = a * abscissa + b;
                }
            }
        }

        return value;
    }

    std::map<double, double> PhysicObject2D::loadCoefficients(const std::string &filePath) {

        static const double MAX_COEFFICIENTS_VALUE = INFINITY;

        std::map<double, double> coefficients;

        std::ifstream ifstream(filePath);

        while (ifstream) {

            double x = MAX_COEFFICIENTS_VALUE;
            double y = MAX_COEFFICIENTS_VALUE;

            ifstream >> x;
            ifstream >> y;

            if (x != MAX_COEFFICIENTS_VALUE && y != MAX_COEFFICIENTS_VALUE) {
                coefficients[x] = y;
            }
        }

        ifstream.close();

        return coefficients;
    }

    Point PhysicObject2D::findLineIntersection(const Line &line1, const Line &line2, bool *status) {

        *status = false;

        Point solution;

        const Point &firstPointLine1 = line1.first;
        const Point &secondPointLine1 = line1.second;

        Vector vectorLine1 = vectorBetweenPoints(firstPointLine1, secondPointLine1);

        const Point &firstPointLine2 = line2.first;
        const Point &secondPointLine2 = line2.second;

        Vector vectorLine2 = vectorBetweenPoints(firstPointLine2, secondPointLine2);

        if (vectorLine1[X_DIM_VALUE] * vectorLine2[Y_DIM_VALUE] !=
            vectorLine1[Y_DIM_VALUE] * vectorLine2[X_DIM_VALUE]) {

            // equation : y = ax + b

            const double a1 = vectorLine1[Y_DIM_VALUE] / vectorLine1[X_DIM_VALUE];

            const double b1 = firstPointLine1[Y_DIM_VALUE] - a1 * firstPointLine1[X_DIM_VALUE];


            const double a2 = vectorLine2[Y_DIM_VALUE] / vectorLine2[X_DIM_VALUE];

            const double b2 = firstPointLine2[Y_DIM_VALUE] - a2 * firstPointLine2[X_DIM_VALUE];


            const double x = (b2 - b1) / (a1 - a2);

            if (MIN_VALUE(firstPointLine1[X_DIM_VALUE], secondPointLine1[X_DIM_VALUE]) < x &&
                MAX_VALUE(firstPointLine1[X_DIM_VALUE], secondPointLine1[X_DIM_VALUE]) > x &&
                MIN_VALUE(firstPointLine2[X_DIM_VALUE], secondPointLine2[X_DIM_VALUE]) < x &&
                MAX_VALUE(firstPointLine2[X_DIM_VALUE], secondPointLine2[X_DIM_VALUE]) > x) {

                *status = true;

                solution = {x, a1 * x + b1};
            }
        }

        return solution;
    }

    Line PhysicObject2D::constructLine(const Point &point1, const Point &point2) {

        Line line;

        line.first = point1;
        line.second = point2;

        return line;
    }

    double PhysicObject2D::lineLength(const Line &line) {

        return distanceBetweenPoint(line.first, line.second);
    }

    double PhysicObject2D::angleVectorDirection(const Vector &vector1, const Vector &vector2) {

        double angle = angleBetweenVector(vector1, vector2);

        return (angleBetweenVector(vector2, pointRotation(vector1, angle / 2.0)) < angle) ? 1.0 : -1.0;
    }
}