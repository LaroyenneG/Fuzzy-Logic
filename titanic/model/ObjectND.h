
#ifndef LOGIQUEFLOUE_OBJECTND_H
#define LOGIQUEFLOUE_OBJECTND_H

#include <cmath>

#include <array>
#include <vector>

#define INDEX_ERROR_MSG "out of bounds"

#define CHECK_DIMENSION(dim) if (dim > DIM) { throw std::out_of_range(INDEX_ERROR_MSG);}

namespace model {

    template<typename T, unsigned int D>

    class ObjectND {

    public:
        const unsigned int DIM;

    private:
        std::vector<std::array<T, D>> points;     // m

        T position[D];                         // m
        T speed[D];                            // m / s
        T acceleration[D];                     // m / s²
        T orientation[D];                      // no unity

        T weight;                              // kg

    public:
        explicit ObjectND(const std::vector<std::array<T, D>> &_points, const std::array<T, D> &_position,
                          const std::array<T, D> &_speed,
                          const std::array<T, D> &_acceleration, const std::array<T, D> &_orientation,
                          const T &_weight);

        ObjectND(const ObjectND<T, D> &object);

        static T vectorNorm(const T *vector, unsigned int n);

        virtual ~ObjectND() = default;

        T geSpeed() const;

        T geAcceleration() const;

        const T &getAcceleration(unsigned int dim) const;

        const T &getSpeed(unsigned int dim) const;

        const T &getPosition(unsigned int dim) const;

        const T &getOrientation(unsigned int dim) const;

        void setAcceleration(const T &value, unsigned int dim);

        void setSpeed(const T &value, unsigned int dim);

        void setPosition(const T &value, unsigned int dim);

        void setOrientation(const T &value, unsigned int dim);

        void setWeight(const T &value);

        const T &getWeight() const;

        void nextPosition(const T &time);

        void nextSpeed(const T &time);

        void nextTime(const T &time);

        const std::vector<std::array<T, D>> &getPoints() const;

        virtual void writeAbsolutePoints(std::vector<std::array<T, D>> &_points) const = 0;

        virtual bool touch(const ObjectND<T, D> &object) const = 0;

        ObjectND &operator=(const ObjectND &object);
    };

    template<typename T, unsigned int D>
    ObjectND<T, D>::ObjectND(const std::vector<std::array<T, D>> &_points, const std::array<T, D> &_position,
                             const std::array<T, D> &_speed, const std::array<T, D> &_acceleration,
                             const std::array<T, D> &_orientation, const T &_weight)
            : DIM(D), points(_points), weight(_weight) {

        for (unsigned int i = 0; i < DIM; ++i) {
            position[i] = _position[i];
            speed[i] = _speed[i];
            acceleration[i] = _acceleration[i];
            orientation[i] = _orientation[i];
        }
    }

    template<typename T, unsigned int D>
    ObjectND<T, D>::ObjectND(const ObjectND<T, D> &object)
            : DIM(object.DIM), points(object.points), weight(object.weight) {

        for (unsigned int i = 0; i < DIM; ++i) {
            position[i] = object.position[i];
            speed[i] = object.speed[i];
            acceleration[i] = object.acceleration[i];
        }
    }

    template<typename T, unsigned int D>
    const std::vector<std::array<T, D>> &ObjectND<T, D>::getPoints() const {
        return points;
    }

    template<typename T, unsigned int D>
    ObjectND<T, D> &ObjectND<T, D>::operator=(const ObjectND<T, D> &object) {

        if (this != &object) {

            DIM = object.DIM;

            points = object.points;

            for (int i = 0; i < DIM; ++i) {

                position[i] = object.position[i];
                position[i] = object.position[i];

                speed[i] = object.speed[i];
                speed[i] = object.speed[i];

                acceleration[i] = object.acceleration[i];
                acceleration[i] = object.acceleration[i];
            }

            weight = object.weight;
        }

        return *this;
    }

    template<typename T, unsigned int D>
    const T &ObjectND<T, D>::getAcceleration(unsigned int dim) const {

        CHECK_DIMENSION(dim);

        return acceleration[dim];
    }

    template<typename T, unsigned int D>
    const T &ObjectND<T, D>::getSpeed(unsigned int dim) const {

        CHECK_DIMENSION(dim);

        return speed[dim];
    }

    template<typename T, unsigned int D>
    const T &ObjectND<T, D>::getPosition(unsigned int dim) const {

        CHECK_DIMENSION(dim);

        return position[dim];
    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::setAcceleration(const T &value, unsigned int dim) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::setSpeed(const T &value, unsigned int dim) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::setPosition(const T &value, unsigned int dim) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::setWeight(const T &value) {
        weight = value;
    }

    template<typename T, unsigned int D>
    const T &ObjectND<T, D>::getWeight() const {
        return weight;
    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextPosition(const T &time) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextSpeed(const T &time) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextTime(const T &time) {
        nextSpeed(time);
        nextPosition(time);
    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::setOrientation(const T &value, unsigned int dim) {

        CHECK_DIMENSION(dim);

        orientation[dim] = value;
    }

    template<typename T, unsigned int D>
    const T &ObjectND<T, D>::getOrientation(unsigned int dim) const {

        CHECK_DIMENSION(dim);

        return orientation[dim];
    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::writeAbsolutePoints(std::vector<std::array<T, D>> &_points) const {

    }

    template<typename T, unsigned int D>
    T ObjectND<T, D>::geAcceleration() const {
        return vectorNorm(acceleration, D);
    }

    template<typename T, unsigned int D>
    T ObjectND<T, D>::geSpeed() const {
        return vectorNorm(speed, D);
    }

    template<typename T, unsigned int D>
    T ObjectND<T, D>::vectorNorm(const T *vector, unsigned int n) {

        T value = static_cast<T>(0);

        for (unsigned int i = 0; i < n; i++) {
            value += vector[i] * vector[i];
        }

        return sqrt(value);
    }
}

#endif //LOGIQUEFLOUE_OBJECTND_H
