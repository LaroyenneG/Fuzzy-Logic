#ifndef LOGIQUEFLOUE_COGDEFUZZ_H
#define LOGIQUEFLOUE_COGDEFUZZ_H

#include "MamdaniDefuzz.h"

#define COG_DEFUZZ_DEFAULT_MIN 0
#define COG_DEFUZZ_DEFAULT_MAX 10
#define COG_DEFUZZ_DEFAULT_STEP 1

namespace fuzzylogic::fuzzy {

    template<typename T>
    class CogDefuzz : public MamdaniDefuzz<T> {

    public:
        explicit CogDefuzz(const T &_min, const T &_max, const T &_step);

        explicit CogDefuzz();

        T defuzz(const Shape<T> &shape) const override;
    };

    template<typename T>
    CogDefuzz<T>::CogDefuzz(const T &_min, const T &_max, const T &_step)
            : MamdaniDefuzz<T>(_min, _max, _step) {
    }

    template<typename T>
    CogDefuzz<T>::CogDefuzz() : CogDefuzz(COG_DEFUZZ_DEFAULT_MIN, COG_DEFUZZ_DEFAULT_MAX, COG_DEFUZZ_DEFAULT_STEP) {

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
