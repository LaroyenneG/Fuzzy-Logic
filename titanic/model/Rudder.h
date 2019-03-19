
#ifndef LOGIQUEFLOUE_RUDDER_H
#define LOGIQUEFLOUE_RUDDER_H

#include <utility>
#include <array>

#include "Object2D.h"

#define RUDDER_DEFAULT_VALUE 0.0
#define RUDDER_DEFAULT_W_SPEED_X 0.0
#define RUDDER_DEFAULT_W_SPEED_Y 0.0
#define RUDDER_DEFAULT_SIZE 4.9


namespace model {

    class Rudder {

    private:
        double value;                           // radian
        double waterSpeed[SPACE_DIMENSION];     // m / s
        double size;                            // m

    public:
        explicit Rudder(double _value, double _xWaterSpeed, double _yWaterSpeed, double _size);

        explicit Rudder();

        void setWaterSpeedX(double xValue);

        void setWaterSpeedY(double yValue);

        void setValue(double _value);

        double getValue() const;

        std::array<double, SPACE_DIMENSION> getVectorStrength() const;
    };
}


#endif //LOGIQUEFLOUE_RUDDER_H
