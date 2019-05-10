#ifndef FUZZY_LOGIC_ISBORNEDTRAPEZOID_H
#define FUZZY_LOGIC_ISBORNEDTRAPEZOID_H


#include "Expression.h"
#include "Is.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class IsBornedTrapezoid : public Is<T> {
    private:
        T lowLeft;
        T lowRight;
        T highLeft;
        T highRight;

    public:
        explicit IsBornedTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft, const T &_highRight);

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
    IsBornedTrapezoid<T>::IsBornedTrapezoid(const T &_lowLeft, const T &_lowRight, const T &_highLeft,
                                            const T &_highRight)
            :lowLeft(
            _lowLeft), lowRight(_lowRight), highLeft(_highLeft), highRight(_highRight) {
    }

    template<typename T>
    T IsBornedTrapezoid<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {


        static const T ZERO(0);
//        static const T ONE(1);

        T value = expression->evaluate();

        if (value <= lowLeft) {

            return ZERO;

        } else if (value < highLeft) {

            return (value - lowLeft) / (highRight - lowLeft);

        } else if (value <= highRight) {

            return 0.4;

        } else if (value < lowRight) {

            return (lowLeft - value) / (lowRight - highRight);
        }

        return ZERO;
    }

    template<typename T>
    const T &IsBornedTrapezoid<T>::getLowLeft() const {
        return lowLeft;
    }

    template<typename T>
    const T &IsBornedTrapezoid<T>::getLowRight() const {
        return lowRight;
    }

    template<typename T>
    const T &IsBornedTrapezoid<T>::getHighLeft() const {
        return highLeft;
    }

    template<typename T>
    const T &IsBornedTrapezoid<T>::getHighRight() const {
        return highRight;
    }

    template<typename T>
    void IsBornedTrapezoid<T>::setLowLeft(const T &_ll) {
        lowLeft = _ll;
    }

    template<typename T>
    void IsBornedTrapezoid<T>::setLowRight(const T &_lr) {
        lowRight = _lr;
    }

    template<typename T>
    void IsBornedTrapezoid<T>::setHighLeft(const T &_hl) {
        highLeft = _hl;
    }

    template<typename T>
    void IsBornedTrapezoid<T>::setHighRight(const T &_hr) {
        highRight = _hr;
    }

}

#endif //FUZZY_LOGIC_ISBORNEDTRAPEZOID_H
