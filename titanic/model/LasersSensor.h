#ifndef LOGIQUEFLOUE_LASERSSENSOR_H
#define LOGIQUEFLOUE_LASERSSENSOR_H

#include <array>
#include <map>

#include "PhysicObject2D.h"

#define INVALID_CONFIG_MESSAGE "invalid configuration, cannot create one laser with a angle"


namespace model {

    template<unsigned int N>

    class LasersSensor {

    private:
        Point position;

        double orientation;

        const double range;
        const double angle;

    public:
        explicit LasersSensor(double _xPosition, double _yPosition, double _orientation, double _range, double _angle);

        void setPosition(const Point &_position);

        std::array<double, N> getLasersValues(const std::set<PhysicObject2D *> &objects) const;

        std::array<std::pair<Point, Point>, N> getLaserLines(const std::set<PhysicObject2D *> &objects) const;
    };

    template<unsigned int N>
    LasersSensor<N>::LasersSensor(double _xPosition, double _yPosition, double _orientation, double _range,
                                  double _angle)
            : position{{_xPosition, _yPosition}}, orientation(_orientation), range(_range), angle(_angle) {

        if (angle != 0.0 && N <= 1) {
            throw std::out_of_range(INVALID_CONFIG_MESSAGE);
        }
    }

    template<unsigned int N>
    void LasersSensor<N>::setPosition(const Point &_position) {
        position = _position;
    }

    template<unsigned int N>
    std::array<double, N> LasersSensor<N>::getLasersValues(const std::set<PhysicObject2D *> &objects) const {

        std::array<std::pair<Point, Point>, N> lines = getLaserLines(objects);

        std::array<double, N> values;

        for (unsigned int i = 0; i < N; i++) {

            values[i] = PhysicObject2D::normVector(
                    PhysicObject2D::vectorBetweenPoints(lines[i].first, lines[i].second));
        }

        return values;
    }

    template<unsigned int N>
    std::array<std::pair<Point, Point>, N>
    LasersSensor<N>::getLaserLines(const std::set<PhysicObject2D *> &objects) const {

        const double step = angle / N;

        std::array<std::pair<Point, Point>, N> lines;


        if (N > 0) {

            double deviation = -angle / 2.0;

            for (unsigned int i = 0; i < N; ++i) {

                Vector direction = PhysicObject2D::pointRotation(Vector{{cos(orientation), sin(orientation)}},
                                                                 deviation);

                double m = direction[Y_DIM_VALUE] / direction[X_DIM_VALUE];

                double p = position[Y_DIM_VALUE] - m * position[X_DIM_VALUE];

                for (auto object : objects) {

                    std::vector<Point> points;

                    object->writeAbsolutePoints(points);

                    std::cout << p;
                }

                deviation += step;
            }
        }

        return lines;
    }
}


#endif //LOGIQUEFLOUE_LASERSSENSOR_H
