#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <vector>
#include <array>
#include <cmath>

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

namespace view {
    class Draftsman;
}

namespace model {

    class PhysicObject2D {

    private:
        std::vector<std::array<double, MODEL_SPACE_DIMENSION>> points;     // m

        std::array<double, MODEL_SPACE_DIMENSION> position;                  // m
        std::array<double, MODEL_SPACE_DIMENSION> speed;                     // m / s
        std::array<double, MODEL_SPACE_DIMENSION> acceleration;             // m / s²

        double orientation;
        double rotationSpeed;
        double rotationAcceleration;
        double weight;                                                    // kg

    protected:
        static double orientationConverterX(double course);

        static double orientationConverterY(double course);

    public:

        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                double _xPosition,
                                double _yPosition,
                                double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                double _orientation, double rotationSpeed, double rotationAcceleration,
                                double _weight);


        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                double _xPosition,
                                double _yPosition, double _orientation, double _weight);


        bool touch(const PhysicObject2D &object) const;

        void writeAbsolutePoints(std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points) const;

        double getPositionX() const;

        double getPositionY() const;

        void setPositionX(double value);

        void setPositionY(double value);

        void setSpeedX(double value);

        void setSpeedY(double value);

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

        const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &getPoints() const;

        virtual void drawMe(view::Draftsman *draftsman);

        virtual ~PhysicObject2D() = default;
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H