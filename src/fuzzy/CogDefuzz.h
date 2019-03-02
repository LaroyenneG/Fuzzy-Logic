#ifndef LOGIQUEFLOUE_COGDEFUZZ_H
#define LOGIQUEFLOUE_COGDEFUZZ_H

#include "MamdaniDefuzz.h"

namespace fuzzy {

    template<typename T>
    class CogDefuzz : public MamdaniDefuzz<T> {

        virtual T defuzz(const Shape<T> *shape) const;
    };

    template<typename T>
    T CogDefuzz<T>::defuzz(const Shape<T> *shape) const {
        return 0;
    }
}


#endif //LOGIQUEFLOUE_COGDEFUZZ_H
