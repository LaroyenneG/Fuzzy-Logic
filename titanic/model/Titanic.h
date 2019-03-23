
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <cmath>
#include <map>
#include <vector>
#include <list>


#include "PhysicObject2D.h"
#include "Engine.h"
#include "Rudder.h"

#define SEA_M_VOL 1025.0            // kg/m^3


#define TITANIC_DEFAULT_COURSE 3.1416 / 2.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0
#define TITANIC_DEFAULT_X 0.0
#define TITANIC_DEFAULT_Y 0.0

#define TITANIC_DRAUGHT 10.5 // m
#define TITANIC_REFERENCE_SURFACE 2824.5 // m²
#define TITANIC_ENGINES_COUNTER 3

#define TITANIC_DEFAULT_POINTS_FILE_NAME "../assets/titanic_shape_points.txt"
#define TITANIC_DEFAULT_LIFT_COEFFICIENTS_FILE_NAME "../assets/titanic_lift_coefficients.txt"
#define TITANIC_DEFAULT_DRAG_COEFFICIENTS_FILE_NAME "../assets/titanic_drag_coefficients.txt"

#define TITANIC_ALTERNATIVE_MACHINE_1_RANK 0
#define TITANIC_ALTERNATIVE_MACHINE_2_RANK 1
#define TITANIC_TURBINE_MACHINE_RANK 2

namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const std::map<double, double> lift_coefficients;
        const std::map<double, double> drag_coefficients;

        Rudder rudder;

        const std::array<Engine *, TITANIC_ENGINES_COUNTER> engines;


    public:
        explicit Titanic(const std::vector<Point> &points, double _orientation, double _weight, double _xPosition,
                         double _yPosition,
                         const std::map<double, double> &_lift_coefficients,
                         const std::map<double, double> &_drag_coefficients);

        explicit Titanic(double x, double y, double _orientation);

        explicit Titanic();

        ~Titanic() override;

        double approximatedLiftCoefficient(double incidence) const;

        double approximatedDragCoefficient(double incidence) const;

        void nextTime(double time) override;

        void setMachinePower(double value);

        void setRudderValue(double value);

        std::array<double, TITANIC_ENGINES_COUNTER> getMachinesRotationSpeed() const;


        /********************* strengths ************************/

        Vector computePropulsion(double time) const;

        Vector computeDrag(double time) const;

        Vector computeLift(double time) const;


        /*********************** static functions *********************/

        static double estimateOrdinateValue(double abscissa, const std::map<double, double> &points);

        static std::map<double, double> loadCoefficients(std::string filePath);
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
