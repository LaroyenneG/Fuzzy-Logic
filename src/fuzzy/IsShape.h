#ifndef LOGIQUEFLOUE_ISSHAPE_H
#define LOGIQUEFLOUE_ISSHAPE_H

#include "Is.h"
#include "Shape.h"

namespace fuzzy {

    template<typename T>
    class IsShape : public Is<T> {

    private:
        Shape<T> shape;

    public:
        explicit IsShape(const Shape<T> &_shape);

        T evaluate(core::Expression<T> *expression) const override;

        void setShape(const Shape<T> &_shape);

        const Shape<T> &getShape() const;
    };

    template<typename T>
    T IsShape<T>::evaluate(core::Expression<T> *expression) const {
        return 0;
    }

    template<typename T>
    IsShape<T>::IsShape(const Shape<T> &_shape)
            : shape(_shape) {
    }

    template<typename T>
    void IsShape<T>::setShape(const Shape<T> &_shape) {
        shape = _shape;
    }

    template<typename T>
    const Shape<T> &IsShape<T>::getShape() const {
        return shape;
    }
}


#endif //LOGIQUEFLOUE_ISSHAPE_H
