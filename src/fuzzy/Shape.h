#ifndef LOGIQUEFLOUE_SHAPE_H
#define LOGIQUEFLOUE_SHAPE_H

#include <vector>
#include <exception>
#include <map>

#include "ShapeSerializationException.h"
#include "PointAlreadyAddedShapeException.h"

#define OPEN_SET_CHAR '['
#define CLOSE_SET_CHAR ']'
#define SPACE_CHAR ' '
#define OPEN_POINT_CHAR '('
#define CLOSE_POINT_CHAR ')'

namespace fuzzy {

    template<typename T>
    class Shape {

    public :
        class JavaIterator {

        private:
            const Shape<T> &target;

            typename std::map<T, std::set<T>>::iterator xIterator;
            typename std::set<T>::iterator yIterator;

        public:
            explicit JavaIterator(const Shape<T> &target);

            bool hasNext() const;

            std::pair<T &, T &> next();
        };

    private:
        std::map<T, std::set<T>> points;

        static void serializeMap(const std::map<T, std::set<T>> &map, std::ostream &ostream);

        static void unSerializeMap(std::map<T, std::set<T>> &map, std::istream &istream);

    public:
        explicit Shape() = default;

        Shape(const Shape<T> &shape);

        explicit Shape(std::istream &istream);

        virtual ~Shape() = default;

        void addPoint(const T &x, const T &y);

        void serialize(std::ostream &ostream) const;

        void unSerialize(std::istream &istream);

        virtual bool equals(const Shape<T> &shape) const;

        JavaIterator getIterator() const;

        /* operators */

        std::istream &operator>>(std::istream &istream);

        Shape<T> &operator=(const Shape<T> &shape);

        bool operator==(const Shape<T> &other) const;

        bool operator!=(const Shape<T> &other) const;

        template<typename Y>
        friend std::ostream &operator<<(std::ostream &ostream, const Shape<Y> &shape);
    };

    template<typename T>
    Shape<T>::JavaIterator::JavaIterator(const Shape<T> &target) : xIterator(target.points.begin()), yIterator() {

        if (xIterator != target.points.end()) {
            yIterator = (*xIterator).second.begin();
        }
    }

    template<typename T>
    bool Shape<T>::JavaIterator::hasNext() const {
        return xIterator != target.points.end() && yIterator != *xIterator.second.end();
    }

    template<typename T>
    std::pair<T &, T &> Shape<T>::JavaIterator::next() {

        if (xIterator == target.points.end()) {
            throw std::out_of_range("iterator out of bounds");
        }

        std::pair<T &, T &> pair(*xIterator, *yIterator);

        if (yIterator != (*xIterator).second.end()) {
            yIterator++;
        } else {
            xIterator++;
            yIterator = (*xIterator).second.begin();
        }

        return pair;
    }

    template<typename T>
    Shape<T>::Shape(std::istream &istream) {
        unSerialize(istream);
    }

    template<typename T>
    Shape<T>::Shape(const Shape<T> &shape) : points(shape.points) {
    }

    template<typename T>
    void Shape<T>::addPoint(const T &x, const T &y) {

        auto &set = points[x];

        auto it = set.find(y);
        if (it != set.end()) {
            throw exception::PointAlreadyAddedShapeException();
        }

        points[x].insert(y);
    }

    template<typename T>
    void Shape<T>::serialize(std::ostream &ostream) const {
        serializeMap(points, ostream);
        ostream << std::endl;
    }

    template<typename T>
    void Shape<T>::unSerialize(std::istream &istream) {
        unSerializeMap(points, istream);
    }

    template<typename T>
    void Shape<T>::serializeMap(const std::map<T, std::set<T>> &map, std::ostream &ostream) {

        ostream << OPEN_SET_CHAR;

        for (auto &pair : map) {
            for (auto &y : pair.second) {
                ostream << OPEN_POINT_CHAR;
                ostream << pair.first;
                ostream << SPACE_CHAR;
                ostream << y;
                ostream << CLOSE_POINT_CHAR;
            }
        }

        ostream << CLOSE_SET_CHAR;
    }

    template<typename T>
    void Shape<T>::unSerializeMap(std::map<T, std::set<T>> &map, std::istream &istream) {

        map.clear();

        char c;

        istream >> c;

        bool stopReader = c != OPEN_POINT_CHAR;

        T x;
        T y;

        bool pairLoaded = false;

        while (!stopReader) {

            istream >> c;

            switch (c) {

                case SPACE_CHAR:
                    if (pairLoaded) {
                        throw exception::ShapeSerializationException();
                    }
                    break;

                case OPEN_POINT_CHAR:
                    istream >> x;
                    istream >> y;
                    pairLoaded = true;
                    break;

                case CLOSE_POINT_CHAR:

                    if (pairLoaded) {
                        pairLoaded = false;
                    } else {
                        throw exception::ShapeSerializationException();
                    }

                    map[x].insert(y);

                    break;

                case CLOSE_SET_CHAR:
                    stopReader = true;
                    break;

                default:
                    throw exception::ShapeSerializationException();
            }
        }
    }

    template<typename T>
    bool Shape<T>::equals(const Shape<T> &shape) const {
        return this == &shape || shape.points == points;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &ostream, const Shape<T> &shape) {

        shape.serialize(ostream);

        return ostream;
    }

    template<typename T>
    std::istream &Shape<T>::operator>>(std::istream &istream) {

        unSerialize(istream);

        return istream;
    }

    template<typename T>
    bool Shape<T>::operator==(const Shape<T> &other) const {
        return equals(other);
    }

    template<typename T>
    Shape<T> &Shape<T>::operator=(const Shape<T> &shape) {

        if (this != &shape) {
            points = shape.points;
        }

        return *this;
    }

    template<typename T>
    bool Shape<T>::operator!=(const Shape<T> &other) const {
        return !equals(other);
    }

    template<typename T>
    typename Shape<T>::JavaIterator Shape<T>::getIterator() const {
        return Shape::JavaIterator(*this);
    }
}


#endif //LOGIQUEFLOUE_SHAPE_H
