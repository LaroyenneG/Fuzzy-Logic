#ifndef LOGIQUEFLOUE_SHAPE_H
#define LOGIQUEFLOUE_SHAPE_H

#include <vector>
#include <exception>
#include <map>

#include "PointAlreadyAddedShapeException.h"

namespace fuzzy {

    template<typename T>
    class Shape {
    private:
        std::pair<std::vector<T>, std::vector<T>> points;

    public:
        explicit Shape() = default;

        void addPoint(const T &x, const T &y);

        const T &getX(unsigned int n) const;

        const T &getY(unsigned int n) const;
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

        if (n >= points.first.size()) {
            throw std::out_of_range("invalid index");
        }

        return &points.first[n];
    }

    template<typename T>
    const T &Shape<T>::getY(unsigned int n) const {

        if (n >= points.second.size()) {
            throw std::out_of_range("invalid index");
        }

        return &points.second[n];
    }
}


#endif //LOGIQUEFLOUE_SHAPE_H
