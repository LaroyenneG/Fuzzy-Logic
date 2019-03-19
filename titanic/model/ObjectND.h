
#ifndef LOGIQUEFLOUE_OBJECTND_H
#define LOGIQUEFLOUE_OBJECTND_H


#include <array>
#include <set>

#define INDEX_ERROR_MSG "out of bounds"

#define CHECK_DIMENSION(dim) if (dim > DIM) { throw std::out_of_range(INDEX_ERROR_MSG);}

namespace model {

    template<typename T, unsigned int D>

    class ObjectND {

    public:
        const unsigned int DIM;

    private:
        std::set<std::array<T, D>> points;     // m

        T position[D];                         // m
        T speed[D];                            // m / s
        T acceleration[D];                     // m / s²

        T weight;                              // kg

    public:
        explicit ObjectND(const std::set<std::array<T, D>> &_points, const T *_position, const T *_speed,
                          const T *_acceleration, const T &_weight);

        ObjectND(const ObjectND &object);

        virtual ~ObjectND() = default;

        const T &getAcceleration(unsigned int dim) const;

        const T &getSpeed(unsigned int dim) const;

        const T &getPosition(unsigned int dim) const;

        void setAcceleration(const T &value, unsigned int dim);

        void setSpeed(const T &value, unsigned int dim);

        void setPosition(const T &value, unsigned int dim);

        void setWeight(const T &value);

        const T &getWeight() const;

        bool touch(const ObjectND &object);

        void nextPosition(const T &time);

        void nextSpeed(const T &time);

        void nextTime(const T &time);

        const std::set<std::array<T, D>> &getPoints() const;

        ObjectND &operator=(const ObjectND &object);
    };

    template<typename T, unsigned int D>
    ObjectND<T, D>::ObjectND(const std::set<std::array<T, D>> &_points, const T *_position, const T *_speed,
                             const T *_acceleration, const T &_weight)
            : DIM(D), points(_points), weight(_weight) {

        for (unsigned int i = 0; i < DIM; ++i) {
            position[i] = _position[i];
            speed[i] = _speed[i];
            acceleration[i] = _acceleration[i];
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
    const std::set<std::array<T, D>> &ObjectND<T, D>::getPoints() const {
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
    bool ObjectND<T, D>::touch(const ObjectND &object) {
        return false;
    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextPosition(const T &time) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextSpeed(const T &time) {

    }

    template<typename T, unsigned int D>
    void ObjectND<T, D>::nextTime(const T &time) {

    }
}


#endif //LOGIQUEFLOUE_OBJECTND_H
