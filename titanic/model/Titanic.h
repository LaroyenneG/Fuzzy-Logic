
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <cmath>
#include <vector>

#include "PhysicObject2D.h"
#include "Engine.h"
#include "Rudder.h"

#define SEA_M_VOL 1025.0            // kg/m^3


#define TITANIC_DEFAULT_COURSE 3.1416 / 2.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0
#define TITANIC_DEFAULT_X 0.0
#define TITANIC_DEFAULT_Y 0.0

#define DRAUGHT 10.5 // m
#define REFERENCE_SURFACE 2824.5 // m²


#define ENGINES_COUNTER 3

namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const static std::set<Point> LIFT_COEFFICIENTS;

        const static std::set<Point> DRAG_COEFFICIENTS;

        const static std::vector<Point> DEFAULT_POINTS;

        Rudder rudder;

        const std::array<Engine *, ENGINES_COUNTER> engines;


    public:
        explicit Titanic(const std::vector<Point> &points, double _orientation,
                         double _weight,
                         double _xPosition, double _yPosition);

        explicit Titanic(double x, double y, double _orientation);

        explicit Titanic();

        ~Titanic() override;

        double approximatedLiftCoefficient(double incidence) const;

        double approximatedDragCoefficient(double incidence) const;

        void nextTime(double time) override;

        void setMachinePower(double value);

        void setRudderValue(double value);

        std::array<double, ENGINES_COUNTER> getMachinesRotationSpeed() const;


        Vector computePropulsion(double time) const;

        Vector computeDrag(double time) const;

        Vector computeLift(double time) const;
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
