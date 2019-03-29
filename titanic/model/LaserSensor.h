#ifndef LOGIQUEFLOUE_LASERSENSOR_H
#define LOGIQUEFLOUE_LASERSENSOR_H

#include <array>
#include <map>

#include "PhysicObject2D.h"


namespace model {

    template<unsigned int N>
    class LaserSensor {

    private:
        Point position;

        double orientation;

        const double range;
        const double angle;

    public:
        explicit LaserSensor(double _xPosition, double _yPosition, double _orientation, double _range, double _angle);

        void setPosition(const Point &_position);

        std::array<double, N> getLasersValues(const std::set<PhysicObject2D *> &objects) const;

        std::array<std::pair<Point, Point>, N> getLaserLines(const std::set<PhysicObject2D *> &objects) const;
    };

    template<unsigned int N>
    LaserSensor<N>::LaserSensor(double _xPosition, double _yPosition, double _orientation, double _range, double _angle)
            : position{{_xPosition, _yPosition}}, orientation(_orientation), range(_range), angle(_angle) {

    }

    template<unsigned int N>
    void LaserSensor<N>::setPosition(const Point &_position) {
        position = _position;
    }

    template<unsigned int N>
    std::array<double, N> LaserSensor<N>::getLasersValues(const std::set<PhysicObject2D *> &objects) const {
        return std::array<double, N>();
    }

    template<unsigned int N>
    std::array<std::pair<Point, Point>, N>
    LaserSensor<N>::getLaserLines(const std::set<PhysicObject2D *> &objects) const {
        return std::array<std::pair<Point, Point>, N>();
    }
}


#endif //LOGIQUEFLOUE_LASERSENSOR_H
