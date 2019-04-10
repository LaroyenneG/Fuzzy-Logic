#ifndef LOGIQUEFLOUE_LASERSSENSORS_H
#define LOGIQUEFLOUE_LASERSSENSORS_H

#include <array>
#include <map>

#include "PhysicObject2D.h"

#define LASERS_SENSORS_DEFAULT_RANGE 800 // m
#define LASERS_SENSORS_DEFAULT_ANGLE (3.1416/24.0) // radian


#define INVALID_CONFIG_MESSAGE "invalid configuration, cannot create one laser with an angle"


namespace model {

    template<unsigned int N>

    class LasersSensors {

    private:
        Point position;

        double orientation; // radian

        const double range; // m
        const double angle; // radian

    public:
        explicit LasersSensors(double _xPosition, double _yPosition, double _orientation, double _range, double _angle);

        explicit LasersSensors();

        void setPosition(const Point &_position);

        void setOrientation(double _orientation);

        std::array<double, N> getLasersValues(const std::set<PhysicObject2D *> &objects) const;

        std::array<Line, N> getLaserLines(const std::set<PhysicObject2D *> &objects) const;
    };

    template<unsigned int N>
    LasersSensors<N>::LasersSensors() : LasersSensors(DEFAULT_POSITION_X, DEFAULT_POSITION_Y, DEFAULT_ORIENTATION,
                                                      LASERS_SENSORS_DEFAULT_RANGE, LASERS_SENSORS_DEFAULT_ANGLE) {

    }

    template<unsigned int N>
    LasersSensors<N>::LasersSensors(double _xPosition, double _yPosition, double _orientation, double _range,
                                    double _angle)
            : position{{_xPosition, _yPosition}}, orientation(_orientation), range(_range), angle(_angle) {

        if (angle != 0.0 && N <= 1) {
            throw std::out_of_range(INVALID_CONFIG_MESSAGE);
        }
    }

    template<unsigned int N>
    void LasersSensors<N>::setPosition(const Point &_position) {
        position = _position;
    }

    template<unsigned int N>
    void LasersSensors<N>::setOrientation(double _orientation) {
        orientation = _orientation;
    }

    template<unsigned int N>
    std::array<double, N> LasersSensors<N>::getLasersValues(const std::set<PhysicObject2D *> &objects) const {

        auto laserLines = getLaserLines(objects);

        std::array<double, N> values;

        for (unsigned int i = 0; i < N; i++) {
            values[i] = PhysicObject2D::distanceBetweenPoint(laserLines[i].first, laserLines[i].second) / range;
        }

        return values;
    }

    template<unsigned int N>
    std::array<Line, N>
    LasersSensors<N>::getLaserLines(const std::set<PhysicObject2D *> &objects) const {

        static const unsigned int RELATIVE_SIZE = N - 1;

        std::array<Line, N> laserLines;

        if (N > 0) {

            // compute deviation for each laser
            double deviations[N];

            unsigned int index = 0;

            deviations[index++] = 0.0;

            for (unsigned int n = 0; n < RELATIVE_SIZE / 2; n++) { // negative laser angle
                deviations[index++] = -angle / RELATIVE_SIZE;
            }

            for (unsigned int p = RELATIVE_SIZE / 2; p < RELATIVE_SIZE; ++p) {  // positive laser angle
                deviations[index++] = angle / RELATIVE_SIZE;
            }

            for (unsigned int i = 0; i < N; ++i) {

                Vector direction = PhysicObject2D::pointRotation(Vector{{cos(orientation), sin(orientation)}},
                                                                 deviations[i]);

                direction[X_DIM_VALUE] *= range;
                direction[Y_DIM_VALUE] *= range;

                Line line1 = PhysicObject2D::constructLine(position,
                                                           PhysicObject2D::pointTranslation(position, direction));

                double maxDistance = PhysicObject2D::lineLength(line1);
                laserLines[i] = line1;

                for (auto object : objects) {

                    std::vector<Point> points;

                    object->writeAbsolutePoints(points);

                    for (unsigned int j = 0; j < points.size() - 1; j++) {

                        Line line2 = PhysicObject2D::constructLine(points[j], points[j + 1]);

                        bool status = false;

                        Point intersection = PhysicObject2D::findLineIntersection(line1, line2, &status);

                        if (status) {

                            double distance = PhysicObject2D::distanceBetweenPoint(position, intersection);

                            if (distance < maxDistance) {

                                laserLines[i] = PhysicObject2D::constructLine(position, intersection);
                                maxDistance = distance;
                            }
                        }
                    }
                }
            }
        }

        return laserLines;
    }
}


#endif //LOGIQUEFLOUE_LASERSSENSORS_H
