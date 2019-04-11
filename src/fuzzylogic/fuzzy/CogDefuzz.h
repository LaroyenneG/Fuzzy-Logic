#ifndef LOGIQUEFLOUE_COGDEFUZZ_H
#define LOGIQUEFLOUE_COGDEFUZZ_H

#include "MamdaniDefuzz.h"

namespace fuzzylogic::fuzzy {

    template<typename T>
    class CogDefuzz : public MamdaniDefuzz<T> {

    public:
        explicit CogDefuzz(const T &_min, const T &_max, const T &_step);

        T defuzz(const Shape<T> &shape) const override;
    };

    template<typename T>
    CogDefuzz<T>::CogDefuzz(const T &_min, const T &_max, const T &_step)
            : MamdaniDefuzz<T>(_min, _max, _step) {
    }

    template<typename T>
    T CogDefuzz<T>::defuzz(const Shape<T> &shape) const {

        static const T ZERO(0);

        T numerator(0);
        T denominator(0);

        for (auto point : shape) {

            const T &x = point.first;
            const T &y = point.second;

            numerator += x * y;
            denominator += y;
        }

        return (denominator != ZERO) ? numerator / denominator : ZERO;
    }
}


#endif //LOGIQUEFLOUE_COGDEFUZZ_H
