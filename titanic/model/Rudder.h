
#ifndef LOGIQUEFLOUE_RUDDER_H
#define LOGIQUEFLOUE_RUDDER_H

#include <utility>
#include <array>
#include <map>

#include "Helper.h"
#include "PhysicObject2D.h"

#define RUDDER_DEFAULT_VALUE 0.0
#define RUDDER_DEFAULT_W_SPEED_X 0.0
#define RUDDER_DEFAULT_W_SPEED_Y 0.0
#define RUDDER_DEFAULT_SIZE 4.9
#define RUDDER_MAGIC_NUMBER 0.0001


#define RUDDER_DEFAULT_LIFT_COEFFICIENTS_FILE "../assets/titanic_rudder_lift_coefficients.coef"

namespace model {

    class Rudder {

    private:
        const std::map<double, double> lift_coefficients;

        double value;                                              // radian

        std::array<double, MODEL_SPACE_DIMENSION> waterSpeed;     // m / s

        double size;                                              // m

        double getWaterSpeed() const;

    public:
        explicit Rudder(const std::map<double, double> &_lift_coefficients, double _value, double _xWaterSpeed,
                        double _yWaterSpeed, double _size);

        explicit Rudder();

        void setWaterSpeedX(double xValue);

        void setWaterSpeedY(double yValue);

        void setValue(double _value);

        double getValue() const;

        Vector computeHydrodynamicStrength() const;

        double getReferenceSurface() const;

        double approximatedLiftCoefficient(double incidence) const;

        double approximatedDragCoefficient(double incidence) const;
    };
}


#endif //LOGIQUEFLOUE_RUDDER_H
