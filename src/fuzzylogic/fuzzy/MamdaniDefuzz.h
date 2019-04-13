#ifndef LOGIQUEFLOUE_MAMDANIDEFUZZ_H
#define LOGIQUEFLOUE_MAMDANIDEFUZZ_H

#include <NotValueModelException.h>
#include <ValueModel.h>
#include "BinaryExpression.h"
#include "Shape.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class MamdaniDefuzz : public fuzzylogic::core::BinaryExpression<T> {

    private:
        T min;
        T max;
        T step;

    public:
        explicit MamdaniDefuzz(const T &_min, const T &_max, const T &_step);

        T evaluate(fuzzylogic::core::Expression<T> *left,
                   fuzzylogic::core::Expression<T> *right) const override;

        virtual T defuzz(const Shape<T> &shape) const = 0;

        const T &getMin() const;

        const T &getMax() const;

        const T &getStep() const;

        void setMin(const T &_min);

        void setMax(const T &_max);

        void setStep(const T &_step);
    };

    template<typename T>
    MamdaniDefuzz<T>::MamdaniDefuzz(const T &_min, const T &_max, const T &_step)
            : min(_min), max(_max), step(_step) {
    }

    template<typename T>
    T MamdaniDefuzz<T>::evaluate(fuzzylogic::core::Expression<T> *left,
                                 fuzzylogic::core::Expression<T> *right) const {

        if (!left->isValue()) {
            throw fuzzylogic::exception::NotValueModelException();
        }

        auto valueModel = dynamic_cast<fuzzylogic::core::ValueModel<T> *>(left);

        Shape<T> shape;

        for (T x = min; x < max; x += step) {

            valueModel->setValue(min);

            T y = right->evaluate();

            shape.addPoint(x, y);
        }

        return defuzz(shape);
    }

    template<typename T>
    const T &MamdaniDefuzz<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &MamdaniDefuzz<T>::getMax() const {
        return max;
    }

    template<typename T>
    const T &MamdaniDefuzz<T>::getStep() const {
        return step;
    }

    template<typename T>
    void MamdaniDefuzz<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void MamdaniDefuzz<T>::setMax(const T &_max) {
        max = _max;
    }

    template<typename T>
    void MamdaniDefuzz<T>::setStep(const T &_step) {
        step = _step;
    }
}


#endif //LOGIQUEFLOUE_MAMDANIDEFUZZ_H
