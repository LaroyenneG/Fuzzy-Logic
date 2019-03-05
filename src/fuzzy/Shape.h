#ifndef LOGIQUEFLOUE_SHAPE_H
#define LOGIQUEFLOUE_SHAPE_H

#include <vector>
#include <exception>
#include <map>

#include "PointAlreadyAddedShapeException.h"

#define INDEX_ERROR_MSG "invalid index"

namespace fuzzy {

    template<typename T>
    class Shape {
    private:
        std::pair<std::vector<T>, std::vector<T>> points;

        void safeIndexX(unsigned int n) const;

        void safeIndexY(unsigned int n) const;

    public:
        explicit Shape() = default;

        void addPoint(const T &x, const T &y);

        const T &getX(unsigned int n) const;

        T &getX(unsigned int n);

        const T &getY(unsigned int n) const;

        T &getY(unsigned int n);


        friend std::ostream &operator<<(std::ostream &ostream, const Shape<T> &shape);
    };

    template<typename T>
    void Shape<T>::addPoint(const T &x, const T &y) {

        for (int i = 0; i < points.first.size(); ++i) {
            if (points.first[i] == x && points.second[i] == y) {
                throw exception::PointAlreadyAddedShapeException();
            }
        }

        points.first.push_back(x);
        points.second.push_back(y);
    }

    template<typename T>
    const T &Shape<T>::getX(unsigned int n) const {

        safeIndexX(n);

        return &points.first[n];
    }

    template<typename T>
    const T &Shape<T>::getY(unsigned int n) const {

        safeIndexY(n);

        return &points.second[n];
    }

    template<typename T>
    void Shape<T>::safeIndexX(unsigned int n) const {

        if (n >= points.first.size()) {
            throw std::out_of_range(INDEX_ERROR_MSG);
        }
    }

    template<typename T>
    void Shape<T>::safeIndexY(unsigned int n) const {

        if (n >= points.second.size()) {
            throw std::out_of_range(INDEX_ERROR_MSG);
        }
    }

    template<typename T>
    T &Shape<T>::getX(unsigned int n) {

        safeIndexX(n);

        return &points.first[n];
    }

    template<typename T>
    T &Shape<T>::getY(unsigned int n) {

        safeIndexY(n);

        return &points.second[n];
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &ostream, const Shape<T> &shape) {
        return ostream;
    }
}


#endif //LOGIQUEFLOUE_SHAPE_H
