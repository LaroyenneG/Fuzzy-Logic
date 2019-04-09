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

#define OUT_OF_BOUND "iterator out of bound"

namespace fuzzy {

    template<typename T>
    class Shape {

    public :
        class iterator {

        private:
            typename std::map<T, std::set<T>>::const_iterator xIterator;
            typename std::map<T, std::set<T>>::const_iterator xEnd;

            typename std::set<T>::iterator yIterator;
            typename std::set<T>::iterator yEnd;

        public:
            explicit iterator(const Shape<T> &target, bool type);

            iterator(const iterator &it);

            std::pair<const T &, const T &> operator*() const;

            void operator++(int);

            void operator++();

            bool equals(const iterator &it) const;

            bool operator==(const iterator &it) const;

            bool operator!=(const iterator &it) const;

            void next();

            iterator &operator=(const iterator &iterator);
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

        iterator begin() const;

        iterator end() const;

        unsigned long size() const;

        /* operators */

        std::istream &operator>>(std::istream &istream);

        Shape<T> &operator=(const Shape<T> &shape);

        bool operator==(const Shape<T> &other) const;

        bool operator!=(const Shape<T> &other) const;

        template<typename Y>
        friend std::ostream &operator<<(std::ostream &ostream, const Shape<Y> &shape);
    };

    template<typename T>
    Shape<T>::iterator::iterator(const Shape<T> &target, bool type) {

        xIterator = target.points.begin();
        xEnd = target.points.end();

        if (type) {

            if (xIterator != xEnd) {
                yIterator = (*xIterator).second.begin();
                yEnd = (*xIterator).second.end();
            }
        } else {
            xIterator = xEnd;
        }
    }

    template<typename T>
    Shape<T>::iterator::iterator(const Shape::iterator &it)
            : xIterator(it.xIterator), yIterator(it.yIterator), xEnd(it.xEnd), yEnd(it.yEnd) {
    }

    template<typename T>
    void Shape<T>::iterator::next() {

        yIterator++;

        if (yIterator == yEnd) {

            xIterator++;

            if (xIterator != xEnd) {
                yIterator = (*xIterator).second.begin();
                yEnd = (*xIterator).second.end();
            }
        }
    }

    template<typename T>
    Shape<T>::Shape(std::istream
                    &istream) {
        unSerialize(istream);
    }

    template<typename T>
    Shape<T>::Shape(
            const Shape<T> &shape) : points(shape.points) {
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

        bool stopReader = c != OPEN_SET_CHAR;

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
    typename Shape<T>::iterator Shape<T>::begin() const {
        return Shape::iterator(*this, true);
    }

    template<typename T>
    typename Shape<T>::iterator Shape<T>::end() const {
        return Shape::iterator(*this, false);
    }

    template<typename T>
    unsigned long Shape<T>::size() const {

        unsigned long count = 0;

        for (auto &pair : points) {
            count += pair.second.size();
        }

        return count;
    }

    template<typename T>
    std::pair<const T &, const T &> Shape<T>::iterator::operator*() const {

        if (xIterator == xEnd || yIterator == yEnd) {
            throw std::out_of_range(OUT_OF_BOUND);
        }

        return std::pair<const T &, const T &>((*xIterator).first, *yIterator);
    }

    template<typename T>
    void Shape<T>::iterator::operator++(int) {
        next();
    }

    template<typename T>
    void Shape<T>::iterator::operator++() {
        next();
    }

    template<typename T>
    typename Shape<T>::iterator &Shape<T>::iterator::operator=(const Shape::iterator &iterator) {

        if (&iterator != this) {
            yEnd = iterator.yEnd;
            xEnd = iterator.xEnd;
            xIterator = iterator.xIterator;
            yIterator = iterator.yIterator;
        }

        return *this;
    }

    template<typename T>
    bool Shape<T>::iterator::equals(const Shape::iterator &it) const {

        if (xIterator == xEnd && it.xIterator == it.xEnd) {
            return true;
        }

        return xIterator == it.xIterator && yIterator == it.yIterator;
    }

    template<typename T>
    bool Shape<T>::iterator::operator==(const Shape::iterator &it) const {
        return equals(it);
    }

    template<typename T>
    bool Shape<T>::iterator::operator!=(const Shape::iterator &it) const {
        return !equals(it);
    }
}


#endif //LOGIQUEFLOUE_SHAPE_H
