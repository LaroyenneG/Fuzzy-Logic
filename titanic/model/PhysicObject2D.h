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

#define MODEL_SPACE_DIMENSION 2

namespace model {

    class PhysicObject2D : public ObjectND<double, MODEL_SPACE_DIMENSION> {

    public:
        explicit PhysicObject2D(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &_points, double _xPosition,
                                double _yPosition,
                                double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration, double _weight);

        explicit PhysicObject2D(const std::set<std::array<double, MODEL_SPACE_DIMENSION>> &_points, double _weight);

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

        ~PhysicObject2D() override = default;
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H