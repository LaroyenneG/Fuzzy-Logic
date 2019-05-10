#ifndef LOGIQUEFLOUE_ISTRAPEZOID_H
#define LOGIQUEFLOUE_ISTRAPEZOID_H

#include "Expression.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class IsTrapezoid : public Is<T> {
    private:
        T lowLeft;
        T lowRight;
        T highLeft;
        T highRight;

    public:
        explicit IsTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft, const T &_highRight);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getLowLeft() const;

        const T &getLowRight() const;

        const T &getHighLeft() const;

        const T &getHighRight() const;

        void setLowLeft(const T &_ll);

        void setLowRight(const T &_lr);

        void setHighLeft(const T &_hl);

        void setHighRight(const T &_hr);
    };

    template<typename T>
    IsTrapezoid<T>::IsTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft, const T &_highRight)
            :lowLeft(
            _lowLeft), lowRight(_lowRight), highLeft(_highLeft), highRight(_highRight) {
    }

    template<typename T>
    T IsTrapezoid<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        static const T ZERO(0);
        static const T ONE(1);

        T value = expression->evaluate();

        if (value <= lowLeft) {

            return ZERO;

        } else if (value < highLeft) {

            return (value - lowLeft) / (highRight - lowLeft);

        } else if (value <= highRight) {

            return ONE;

        } else if (value < lowRight) {

            return (lowLeft - value) / (lowRight - highRight);
        }

        return ZERO;
    }

    template<typename T>
    const T &IsTrapezoid<T>::getLowLeft() const {
        return lowLeft;
    }

    template<typename T>
    const T &IsTrapezoid<T>::getLowRight() const {
        return lowRight;
    }

    template<typename T>
    const T &IsTrapezoid<T>::getHighLeft() const {
        return highLeft;
    }

    template<typename T>
    const T &IsTrapezoid<T>::getHighRight() const {
        return highRight;
    }

    template<typename T>
    void IsTrapezoid<T>::setLowLeft(const T &_ll) {
        lowLeft = _ll;
    }

    template<typename T>
    void IsTrapezoid<T>::setLowRight(const T &_lr) {
        lowRight = _lr;
    }

    template<typename T>
    void IsTrapezoid<T>::setHighLeft(const T &_hl) {
        highLeft = _hl;
    }

    template<typename T>
    void IsTrapezoid<T>::setHighRight(const T &_hr) {
        highRight = _hr;
    }

}

#endif //LOGIQUEFLOUE_ISTRAPEZOID_H
