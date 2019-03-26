#include "PhysicObject2D.h"
#include "Draftsman.h"


double model::PhysicObject2D::estimateOrdinateValue(double abscissa, const std::map<double, double> &points) {

    std::__cxx11::list<std::pair<double, double>> sortedPoints;

    for (auto &point : points) {
        sortedPoints.push_front(point);
    }

    sortedPoints.sort([](const std::pair<double, double> &p1, const std::pair<double, double> &p2) {
        return p1.first < p2.first;
    });

    double value = 0.0;

    if (sortedPoints.size() >= 2) {

        std::pair<double, double> leftPoint(0.0, 0.0);

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


        std::pair<double, double> rightPoint(0.0, 0.0);

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


        if (initRight && initLeft && leftPoint.first != rightPoint.first) {

            double a = (rightPoint.second - leftPoint.second) / (rightPoint.first - leftPoint.first);

            double b = leftPoint.second - a * leftPoint.first;

            value = a * abscissa + b;
        }
    }

    return value;
}

std::map<double, double> model::PhysicObject2D::loadCoefficients(std::__cxx11::string filePath) {

    static const double MAX_INCIDENCE_VALUE = 3.5;

    std::map<double, double> coefficients;

    std::ifstream ifstream(filePath);

    while (ifstream) {

        double x = MAX_INCIDENCE_VALUE;
        double y = MAX_INCIDENCE_VALUE;

        ifstream >> x;
        ifstream >> y;

        if (x != MAX_INCIDENCE_VALUE && y != MAX_INCIDENCE_VALUE) {
            coefficients[x] = y;
        }
    }

    ifstream.close();

    return coefficients;
}

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

    double PhysicObject2D::distance(const PhysicObject2D &object) const {

        std::vector<Point> myPoints;
        writeAbsolutePoints(myPoints);

        std::vector<Point> objectPoints;
        object.writeAbsolutePoints(objectPoints);

        bool init = false;
        double best = 0.0;

        for (auto myPoint : myPoints) {

            for (auto objectPoint : objectPoints) {

                double distance = distanceBetweenPoint(myPoint, objectPoint);

                if (!init || best > distance) {
                    best = distance;
                    init = true;
                }
            }
        }

        return best;
    }

    bool PhysicObject2D::touch(const PhysicObject2D &object) const {

        std::vector<Point> shape1;
        writeAbsolutePoints(shape1);

        std::vector<Point> shape2;
        object.writeAbsolutePoints(shape2);

        /********************************************************************/

        for (unsigned int i = 0; !shape1.empty() && i < shape1.size() - 1; ++i) {

            Point &point1Set1 = shape1[i];
            Point &point2Set1 = shape1[i + 1];

            Point v1{{point2Set1[X_DIM_VALUE] - point1Set1[X_DIM_VALUE],
                             point2Set1[Y_DIM_VALUE] - point1Set1[Y_DIM_VALUE]}};

            for (unsigned int j = 0; !shape2.empty() && j < shape2.size() - 1; ++j) {

                Point &point1Set2 = shape2[j];
                Point &point2Set2 = shape2[j + 1];

                Vector v2{{point2Set2[X_DIM_VALUE] - point1Set2[X_DIM_VALUE],
                                  point2Set2[Y_DIM_VALUE] - point1Set2[Y_DIM_VALUE]}};

                if (v1[X_DIM_VALUE] * v2[Y_DIM_VALUE] != v1[Y_DIM_VALUE] * v2[X_DIM_VALUE]) {

                    double a1 = (point2Set1[Y_DIM_VALUE] - point1Set1[Y_DIM_VALUE]) /
                                (point2Set1[X_DIM_VALUE] - point1Set1[X_DIM_VALUE]);
                    double c2 = point1Set1[Y_DIM_VALUE] - a1 * point1Set1[X_DIM_VALUE];

                    double a2 = (point2Set2[Y_DIM_VALUE] - point1Set2[Y_DIM_VALUE]) /
                                (point2Set2[X_DIM_VALUE] - point1Set2[X_DIM_VALUE]);
                    double c1 = point1Set2[Y_DIM_VALUE] - a2 * point1Set2[X_DIM_VALUE];

                    double solution = (c1 - c2) / (a1 - a2);

                    if (MIN_VALUE(point1Set1[X_DIM_VALUE], point2Set1[X_DIM_VALUE]) < solution &&
                        MAX_VALUE(point1Set1[X_DIM_VALUE], point2Set1[X_DIM_VALUE]) > solution &&
                        MIN_VALUE(point1Set2[X_DIM_VALUE], point2Set2[X_DIM_VALUE]) < solution &&
                        MAX_VALUE(point1Set2[X_DIM_VALUE], point2Set2[X_DIM_VALUE]) > solution) {

                        return true;
                    }
                }
            }
        }

        return false;
    }

    Vector PhysicObject2D::computeCentrifugalForce() const {

        Vector strength{{0.0, 0.0}};

        return strength;

        if (positions.size() == POINT_QUEUE_SIZE) {

            Point points[POINT_QUEUE_SIZE];

            int index = 0;
            for (auto it = positions.begin(); it != positions.end(); it++, index++) {
                points[index] = *it;
            }

            Vector dv1{{points[1][X_DIM_VALUE] - points[0][X_DIM_VALUE],
                               points[1][Y_DIM_VALUE] - points[0][Y_DIM_VALUE]}};
            Vector dv2{{points[2][X_DIM_VALUE] - points[0][X_DIM_VALUE],
                               points[2][Y_DIM_VALUE] - points[0][Y_DIM_VALUE]}};

            double pointAlign = angleBetweenVector(dv1, dv2);

            if (pointAlign != 0.0 && pointAlign != M_PI * 2.0) {

                Point circleCenter = circleSolver(points[0], points[1], points[2]);

                double rayon = distanceBetweenPoint(circleCenter, points[0]);

                Vector direction = vectorBetweenPoints(circleCenter, points[0]);

                double directionNorm = normVector(direction);

                direction[X_DIM_VALUE] /= directionNorm;
                direction[Y_DIM_VALUE] /= directionNorm;

                double value = weight * getSpeed() / rayon;

                strength = {value * direction[X_DIM_VALUE], value * direction[Y_DIM_VALUE]};
            }
        }

        return strength;
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

        if (positions.size() >= POINT_QUEUE_SIZE) {
            positions.pop_front();
        }
        positions.push_back(position);
    }

    double PhysicObject2D::angleBetweenVector(const Vector &v1, const Vector &v2) {

        const double denominator = normVector(v1) * normVector(v2);

        const double numerator = v1[X_DIM_VALUE] * v2[X_DIM_VALUE] + v1[Y_DIM_VALUE] * v2[Y_DIM_VALUE];

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

        Point nPoint;

        nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] * cos(angle) - point[Y_DIM_VALUE] * sin(angle);
        nPoint[Y_DIM_VALUE] = point[X_DIM_VALUE] * sin(angle) + point[Y_DIM_VALUE] * cos(angle);

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

    std::vector<Point> PhysicObject2D::loadShapePoints(std::string filePath) {

        static const double POINT_MAX_VALUE = INFINITY;

        std::vector<Point> points;

        std::ifstream ifstream(filePath);

        while (ifstream) {

            double x = INFINITY;
            double y = INFINITY;

            ifstream >> x;
            ifstream >> y;

            if (x != POINT_MAX_VALUE && y != POINT_MAX_VALUE) {
                points.push_back(Point{{x, y}});
            }
        }

        ifstream.close();

        return points;
    }

    double PhysicObject2D::distanceBetweenPoint(const Point &p1, const Point &p2) {

        double somme = 0.0;

        for (unsigned int i = 0; i < MODEL_SPACE_DIMENSION; ++i) {
            somme += (p1[i] - p2[i]) * (p1[i] - p2[i]);
        }

        return sqrt(somme);
    }

    Point PhysicObject2D::circleSolver(const Point &p1, const Point &p2, const Point &p3) {

        const double MIN_FITNESS = pow(10, -3);

        double a = (p1[X_DIM_VALUE] + p2[X_DIM_VALUE] + p3[X_DIM_VALUE]) / 3.0;
        double b = (p1[Y_DIM_VALUE] + p2[Y_DIM_VALUE] + p3[Y_DIM_VALUE]) / 3.0;

        double valueStep = fabs(a + b);

        double fitness = INFINITY;

        while ((fitness = circleEquationFitness(p1, p2, p3, a, b)) >= MIN_FITNESS) {

            bool changed = false;

            double steps[] = {-valueStep, valueStep};

            for (auto step : steps) {

                double nA = a + step;

                double nFitness = circleEquationFitness(p1, p2, p3, nA, b);

                if (nFitness < fitness) {
                    a = nA;
                    fitness = nFitness;
                    changed = true;
                    break;
                }
            }


            for (auto step : steps) {

                double nB = b + step;

                double nFitness = circleEquationFitness(p1, p2, p3, a, nB);

                if (nFitness < fitness) {
                    b = nB;
                    fitness = nFitness;
                    changed = true;
                    break;
                }
            }

            if (!changed) {
                valueStep /= 2.0;
            }
        }

        return Point{{a, b}};
    }

    double
    PhysicObject2D::circleEquationFitness(const Point &p1, const Point &p2, const Point &p3, double a, double b) {

        double e1 = (p1[X_DIM_VALUE] - a) * (p1[X_DIM_VALUE] - a) + (p1[Y_DIM_VALUE] - b) * (p1[Y_DIM_VALUE] - b);
        double e2 = (p2[X_DIM_VALUE] - a) * (p2[X_DIM_VALUE] - a) + (p2[Y_DIM_VALUE] - b) * (p2[Y_DIM_VALUE] - b);
        double e3 = (p3[X_DIM_VALUE] - a) * (p3[X_DIM_VALUE] - a) + (p3[Y_DIM_VALUE] - b) * (p3[Y_DIM_VALUE] - b);

        double average = (e1 + e2 + e3) / 3.0;

        return fabs(e1 - average) + fabs(e2 - average) + fabs(e3 - average);
    }

    Vector PhysicObject2D::vectorBetweenPoints(const Point &p1, const Point &p2) {

        return Vector{{p2[X_DIM_VALUE] - p1[X_DIM_VALUE], p2[Y_DIM_VALUE] - p1[Y_DIM_VALUE]}};
    }
}