#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <map>

#include "ObjectND.h"

#define DEFAULT_POSITION_X 0.0
#define DEFAULT_POSITION_Y 0.0

#define DEFAULT_SPEED_X 0.0
#define DEFAULT_SPEED_Y 0.0

#define DEFAULT_ACCELERATION_X 0.0
#define DEFAULT_ACCELERATION_Y 0.0

#define DEFAULT_ORIENTATION_X 0.0
#define DEFAULT_ORIENTATION_Y 1.0

#define MODEL_SPACE_DIMENSION 2

#define X_DIM_VALUE 0
#define Y_DIM_VALUE 1

#define MIN_VALUE(a, b) ((a<b) ? a : b)
#define MAX_VALUE(a, b) ((a>b) ? a : b)

namespace view {
    class Draftsman;
}

namespace model {

    class PhysicObject2D : public ObjectND<double, MODEL_SPACE_DIMENSION> {

    protected:
        static double orientationConverterX(double course);

        static double orientationConverterY(double course);

    public:
        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                double _xPosition,
                                double _yPosition,
                                double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                double _xOrientation, double _yOrientation,
                                double _weight);

        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                double _xPosition,
                                double _yPosition, double _xOrientation, double _yOrientation, double _weight);

        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points,
                                double _xPosition,
                                double _yPosition, double _course, double _weight);

        explicit PhysicObject2D(const std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &_points, double _weight);

        bool touch(const ObjectND<double, MODEL_SPACE_DIMENSION> &object) const override;

        void writeAbsolutePoints(std::vector<std::array<double, MODEL_SPACE_DIMENSION>> &points) const override;

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

        double getOrientationX() const;

        double getOrientationY() const;

        void setAccelerationX(double value);

        void setAccelerationY(double value);

        void setOrientationX(double value);

        void setOrientationY(double value);

        virtual void drawMe(view::Draftsman *draftsman);

        ~PhysicObject2D() override = default;
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H