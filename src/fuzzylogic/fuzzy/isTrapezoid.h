#ifndef LOGIQUEFLOUE_ISTRAPEZOID_H
#define LOGIQUEFLOUE_ISTRAPEZOID_H

#include "Expression.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class isTrapezoid : public Is<T> {
    private:
        T lowLeft;
        T lowRight;
        T highLeft;
        T highRight;

    public:
        explicit isTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft, const T &_highRight);

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
    isTrapezoid<T>::isTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft, const T &_highRight)
            :lowLeft(
            _lowLeft), lowRight(_lowRight), highLeft(_highLeft), highRight(_highRight) {
    }

    template<typename T>
    T isTrapezoid<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        T value = expression->evaluate();

        if (value <= lowLeft)
            return 0;
        else if (value < highLeft)
            return (value - lowLeft) / (highRight - lowLeft);
        else if (value <= highRight)
            return 1.0;
        else if (value < lowRight)
            return (lowLeft - value) / (lowRight - highRight);
        else
            return 0;
    }

    template<typename T>
    const T &isTrapezoid<T>::getLowLeft() const {
        return lowLeft;
    }

    template<typename T>
    const T &isTrapezoid<T>::getLowRight() const {
        return lowRight;
    }

    template<typename T>
    const T &isTrapezoid<T>::getHighLeft() const {
        return highLeft;
    }

    template<typename T>
    const T &isTrapezoid<T>::getHighRight() const {
        return highRight;
    }

    template<typename T>
    void isTrapezoid<T>::setLowLeft(const T &_ll) {
        lowLeft = _ll;
    }

    template<typename T>
    void isTrapezoid<T>::setLowRight(const T &_lr) {
        lowRight = _lr;
    }

    template<typename T>
    void isTrapezoid<T>::setHighLeft(const T &_hl) {
        highLeft = _hl;
    }

    template<typename T>
    void isTrapezoid<T>::setHighRight(const T &_hr) {
        highRight = _hr;
    }

}

#endif //LOGIQUEFLOUE_ISTRAPEZOID_H
