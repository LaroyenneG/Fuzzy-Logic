#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <vector>
#include <array>
#include <cmath>
#include <list>
#include <iostream>
#include <map>
#include <fstream>

#define DEFAULT_POSITION_X 0.0
#define DEFAULT_POSITION_Y 0.0

#define DEFAULT_SPEED_X 0.0
#define DEFAULT_SPEED_Y 0.0

#define DEFAULT_ORIENTATION 0.0

#define DEFAULT_ACCELERATION_X 0.0
#define DEFAULT_ACCELERATION_Y 0.0

#define DEFAULT_ROTATION_SPEED 0.0
#define DEFAULT_ROTATION_ACCELERATION 0.0

#define MODEL_SPACE_DIMENSION 2

#define X_DIM_VALUE 0
#define Y_DIM_VALUE 1

#define MIN_VALUE(a, b) ((a<b) ? a : b)
#define MAX_VALUE(a, b) ((a>b) ? a : b)

#define POINT_QUEUE_SIZE 3

namespace view {
    class Draftsman;
}

namespace model {

    typedef std::array<double, MODEL_SPACE_DIMENSION> Vector;
    typedef std::array<double, MODEL_SPACE_DIMENSION> Point;

    class PhysicObject2D {

    protected:
        std::vector<Point> points;     // m

        Point position;                  // m
        Vector speed;                     // m / s
        Vector acceleration;             // m / s²

        double orientation;                                             // radian
        double rotationSpeed;                                           // radian / s
        double rotationAcceleration;                                    // radian / s²

        double weight;                                                    // kg

        std::list<Point> positions;

    public:

        explicit PhysicObject2D(std::vector<Point> _points,
                                double _xPosition,
                                double _yPosition,
                                double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                double _orientation, double rotationSpeed, double rotationAcceleration,
                                double _weight);


        explicit PhysicObject2D(const std::vector<Point> &_points,
                                double _xPosition,
                                double _yPosition, double _orientation, double _weight);


        Vector computeCentrifugalForce() const;

        bool touch(const PhysicObject2D &object) const;

        double distance(const PhysicObject2D &object) const;

        void writeAbsolutePoints(std::vector<Point> &_points) const;

        double getPositionX() const;

        double getPositionY() const;

        void setPositionX(double value);

        void setPositionY(double value);

        void setSpeedX(double value);

        void setSpeedY(double value);

        double getSpeed() const;

        double getSpeedX() const;

        double getSpeedY() const;

        double getAccelerationX() const;

        double getAccelerationY() const;

        void setAccelerationX(double value);

        void setAccelerationY(double value);

        void setOrientation(double value);

        double getOrientation() const;

        double getRotationSpeed() const;

        double getRotationAcceleration() const;

        void setRotationSpeed(double value);

        void setRotationAcceleration(double value);

        double getWeight() const;

        void setWeight(double value);

        virtual void nextTime(double time);

        void nextOrientation(double time);

        void nextPosition(double time);

        void nextSpeed(double time);

        Vector directionVector() const;

        const std::vector<Point> &getPoints() const;

        virtual void drawMe(view::Draftsman *draftsman);

        virtual ~PhysicObject2D() = default;

        /* static functions */

        static Vector inverseVector(const Vector &vector);

        static double angleBetweenVector(const Vector &v1, const Vector &v2);

        static double normVector(const Vector &vector);

        static Point pointRotation(const Point &point, double angle);

        static Point pointTranslation(const Point &point, const Vector &translation);

        static std::vector<Point> loadShapePoints(const std::string &filePath);

        static double distanceBetweenPoint(const Point &p1, const Point &p2);

        static Point circleSolver(const Point &p1, const Point &p2, const Point &p3);

        static Vector vectorBetweenPoints(const Point &p1, const Point &p2);

        static double estimateOrdinateValue(double abscissa, const std::map<double, double> &points);

        static std::map<double, double> loadCoefficients(const std::string &filePath);

        void nextRotationSpeed(double time);
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H