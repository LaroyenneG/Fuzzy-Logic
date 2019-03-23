
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

namespace model {

    class Titanic : public PhysicObject2D {

    private:
        const std::map<double, double> lift_coefficients;
        const std::map<double, double> drag_coefficients;

        Rudder rudder;

        const std::array<Engine *, TITANIC_ENGINES_COUNTER> engines;


    public:
        explicit Titanic(const std::vector<Point> &points, double _orientation,
                         double _weight,
                         double _xPosition, double _yPosition);

        explicit Titanic(double x, double y, double _orientation);

        explicit Titanic();

        void loadLiftCoefficients(std::istream &istream);

        void loadDragCoefficients(std::istream &istream);

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

        double estimateOrdinateValue(double abscissa, const std::map<double, double> &points);
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
