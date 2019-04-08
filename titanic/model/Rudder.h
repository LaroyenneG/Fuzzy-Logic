
#ifndef LOGIQUEFLOUE_RUDDER_H
#define LOGIQUEFLOUE_RUDDER_H

#include <utility>
#include <array>
#include <map>

#include "PhysicObject2D.h"

#define RUDDER_DEFAULT_VALUE 0.0
#define RUDDER_DEFAULT_W_SPEED_X 0.0
#define RUDDER_DEFAULT_W_SPEED_Y 0.0
#define RUDDER_DEFAULT_WIDTH 4.55
#define RUDDER_DEFAULT_HEIGHT 10.54


#define RUDDER_DEFAULT_LIFT_COEFFICIENTS_FILE "../assets/titanic_rudder_lift_coefficients.coef"
#define RUDDER_DEFAULT_DRAG_COEFFICIENTS_FILE "../assets/titanic_rudder_drag_coefficients.coef"

namespace model {

    class Rudder {

    private:
        const std::map<double, double> lift_coefficients;
        const std::map<double, double> drag_coefficients;

        double value;                                              // radian
        double orientation;                                         // radian

        Vector waterSpeed;     // m / s

        const double width;   // m
        const double height; // m

        double getWaterSpeed() const;

    public:
        explicit Rudder(std::map<double, double> _lift_coefficients, std::map<double, double> _drag_coefficients,
                        double _value, double _xWaterSpeed, double _yWaterSpeed, double _width, double _height,
                        double _orientation);

        explicit Rudder();

        double computeIncidence() const;

        void setWaterSpeedX(double xValue);

        void setWaterSpeedY(double yValue);

        double getWaterSpeedX() const;

        double getWaterSpeedY() const;

        void setValue(double _value);

        void setOrientation(double _orientation);

        double getValue() const;

        Vector computeHydrodynamicStrength() const;

        Vector directionVector() const;

        double getReferenceSurface() const;

        double approximatedLiftCoefficient(double incidence) const;

        double approximatedDragCoefficient(double incidence) const;
    };
}


#endif //LOGIQUEFLOUE_RUDDER_H
