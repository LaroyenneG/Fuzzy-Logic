#ifndef LOGIQUEFLOUE_SHAPE_H
#define LOGIQUEFLOUE_SHAPE_H

#include <vector>
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
}


#endif //LOGIQUEFLOUE_SHAPE_H
