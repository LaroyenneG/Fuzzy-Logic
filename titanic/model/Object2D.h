#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <map>

#define DEFAULT_POSITION_X 0.0
#define DEFAULT_POSITION_Y 0.0

#define DEFAULT_SPEED_X 0.0
#define DEFAULT_SPEED_Y 0.0

#define DEFAULT_ACCELERATION_X 0.0
#define DEFAULT_ACCELERATION_Y 0.0

#define DEFAULT_WEIGHT 0.0

#define SPACE_DIMENSION 2

namespace model {

    class Object2D {

    private:
        std::set<std::pair<double, double >> points; // m

        double position[SPACE_DIMENSION];            // m
        double speed[SPACE_DIMENSION];               // m / s
        double acceleration[SPACE_DIMENSION];        // m / s²

        double weight;                               // kg

    public:
        explicit Object2D(const std::set<std::pair<double, double >> &_points, double _xPosition, double _yPosition,
                          double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration, double _weight);

        explicit Object2D(const std::set<std::pair<double, double >> &_points, double _weight);

        Object2D(const Object2D &object);

        bool touch(const Object2D &object);

        double getPositionX() const;

        double getPositionY() const;

        void setPositionX(double value);

        void setPositionY(double value);

        void setWeight(double value);

        double getWeight() const;

        void setSpeedX(double value);

        void setSpeedY(double value);

        double getSpeedX() const;

        double getSpeedY() const;

        double getAccelerationX() const;

        double getAccelerationY() const;

        void setAccelerationX(double value);

        void setAccelerationY(double value);

        void nextPosition(double time);

        void nextSpeed(double time);

        void nextTime(double time);

        const std::set<std::pair<double, double >> &getPoints() const;

        virtual ~Object2D() = default;
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H