
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <cmath>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>


#include "PhysicObject2D.h"
#include "Engine.h"
#include "Rudder.h"
#include "LaserSensor.h"

#define SEA_M_VOL 1025.0            // kg/m^3
#define TITANIC_SIZE 269.0  // m
#define TITANIC_WIDTH 28.0
#define TITANIC_DEFAULT_COURSE 3.1416 / 2.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0
#define TITANIC_DEFAULT_X 0.0
#define TITANIC_DEFAULT_Y 0.0

#define TITANIC_DRAUGHT 10.5 // m
#define TITANIC_REFERENCE_SURFACE 2824.5 // m²
#define TITANIC_ENGINES_COUNTER 3
#define TITANIC_LASERS_COUNTER 3
#define TITANIC_LASERS_RANGE 800 // m
#define TITANIC_LASERS_ANGLE 0.261666667 // radian

#define TITANIC_DEFAULT_POINTS_FILE_NAME "../assets/titanic_shape_points.point"
#define TITANIC_DEFAULT_LIFT_COEFFICIENTS_FILE_NAME "../assets/titanic_lift_coefficients.coef"
#define TITANIC_DEFAULT_DRAG_COEFFICIENTS_FILE_NAME "../assets/titanic_drag_coefficients.coef"

#define TITANIC_DISTANCE_BETWEEN_RUDDER_AND_GRAVITY_CENTER (269.0 / 2.0) // m
#define TITANIC_MOMENT_OF_INERTIA 272447916732.0 // kg/m²

#define TITANIC_ROTATION_FRICTION 0.3

#define TITANIC_ALTERNATIVE_MACHINE_1_RANK 0
#define TITANIC_ALTERNATIVE_MACHINE_2_RANK 1
#define TITANIC_TURBINE_MACHINE_RANK 2


namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const std::map<double, double> lift_coefficients;
        const std::map<double, double> drag_coefficients;

        Rudder rudder;
        LaserSensor<TITANIC_LASERS_COUNTER> laserSensor;

        const std::array<Engine *, TITANIC_ENGINES_COUNTER> engines;


    public:
        explicit Titanic(const std::vector<Point> &points, double _orientation, double _weight, double _xPosition,
                         double _yPosition, std::map<double, double> _lift_coefficients,
                         std::map<double, double> _drag_coefficients, double _range, double _angle);

        explicit Titanic(double x, double y, double _orientation);

        explicit Titanic();

        ~Titanic() override;

        void drawMe(view::Draftsman *draftsman) override;

        double approximatedLiftCoefficient(double incidence) const;

        double approximatedDragCoefficient(double incidence) const;

        void nextTime(double time) override;

        void setMachinePower(double value);

        void setRudderValue(double value);

        std::array<double, TITANIC_ENGINES_COUNTER> getMachinesRotationSpeed() const;

        const LaserSensor<TITANIC_LASERS_COUNTER> &getLaserSensor() const;

        /********************* strengths ************************/

        Vector computePropulsion(double time) const;

        Vector computeDrag(double time) const;

        Vector computeLift(double time) const;

        Vector computeRudder(double time);
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
