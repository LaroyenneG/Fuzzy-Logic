#ifndef LOGIQUEFLOUE_SHAPE_H
#define LOGIQUEFLOUE_SHAPE_H

#include <vector>
#include <exception>
#include <map>

#include "ShapeSerializationException.h"
#include "PointAlreadyAddedShapeException.h"

#define INDEX_ERROR_MSG "invalid index"

#define OPEN_TABLE_CHAR '['
#define CLOSE_TABLE_CHAR ']'
#define SPACE_TABLE_CHAR ' '

namespace fuzzy {

    template<typename T>
    class Shape {
    private:
        std::pair<std::vector<T>, std::vector<T>> points;

        void safeIndexX(unsigned int n) const;

        void safeIndexY(unsigned int n) const;

        static void serializeVector(const std::vector<T> &vector, std::ostream &ostream);

        static void unSerializeVector(std::vector<T> &vector, std::istream &istream);

    public:
        explicit Shape() = default;

        Shape(const Shape<T> &shape);

        explicit Shape(std::istream &istream);

        ~Shape() = default;

        void addPoint(const T &x, const T &y);

        const T &getX(unsigned int n) const;

        T &getX(unsigned int n);

        const T &getY(unsigned int n) const;

        T &getY(unsigned int n);

        void serialize(std::ostream &ostream) const;

        void unSerialize(std::istream &istream);

        unsigned long xSize() const;

        unsigned long ySize() const;

        std::istream &operator>>(std::istream &istream);

        Shape<T> &operator=(const Shape<T> &shape);

        bool operator==(const Shape<T> &other) const;

        template<typename Y>
        friend std::ostream &operator<<(std::ostream &ostream, const Shape<Y> &shape);
    };

    template<typename T>
    Shape<T>::Shape(std::istream &istream) {
        unSerialize(istream);
    }

    template<typename T>
    Shape<T>::Shape(const Shape<T> &shape) : points(shape.points) {
    }

    template<typename T>
    void Shape<T>::addPoint(const T &x, const T &y) {

        for (unsigned int i = 0; i < points.first.size(); ++i) {
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

        return points.first[n];
    }

    template<typename T>
    const T &Shape<T>::getY(unsigned int n) const {

        safeIndexY(n);

        return points.second[n];
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

        return points.first[n];
    }

    template<typename T>
    T &Shape<T>::getY(unsigned int n) {

        safeIndexY(n);

        return points.second[n];
    }

    template<typename T>
    void Shape<T>::serialize(std::ostream &ostream) const {
        serializeVector(points.first, ostream);
        ostream << std::endl;
        serializeVector(points.second, ostream);
        ostream << std::endl;
    }

    template<typename T>
    void Shape<T>::unSerialize(std::istream &istream) {

        points.first.clear();
        points.second.clear();

        unSerializeVector(points.first, istream);
        unSerializeVector(points.second, istream);
    }

    template<typename T>
    void Shape<T>::serializeVector(const std::vector<T> &vector, std::ostream &ostream) {

        ostream << vector.size();

        ostream << SPACE_TABLE_CHAR << OPEN_TABLE_CHAR;

        for (unsigned int i = 0; i < vector.size(); ++i) {

            ostream << vector[i];

            if (i + 1 < vector.size()) {
                ostream << SPACE_TABLE_CHAR;
            }
        }

        ostream << CLOSE_TABLE_CHAR;
    }

    template<typename T>
    void Shape<T>::unSerializeVector(std::vector<T> &vector, std::istream &istream) {

        unsigned int size;

        istream >> size;

        char c;

        istream >> c;

        if (c != OPEN_TABLE_CHAR) {
            throw exception::ShapeSerializationException();
        }

        for (unsigned int i = 0; i < size; ++i) {

            T value = 0;

            istream >> value;

            vector.push_back(value);
        }

        istream >> c;

        if (c != CLOSE_TABLE_CHAR) {
            throw exception::ShapeSerializationException();
        }
    }


    template<typename T>
    unsigned long Shape<T>::xSize() const {
        return points.first.size();
    }

    template<typename T>
    unsigned long Shape<T>::ySize() const {
        return points.second.size();
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

        return this == &other || other.points == points;
    }

    template<typename T>
    Shape<T> &Shape<T>::operator=(const Shape<T> &shape) {

        if (this != &shape) {
            points.first = shape.points.first;
            points.second = shape.points.second;
        }

        return *this;
    }
}


#endif //LOGIQUEFLOUE_SHAPE_H
