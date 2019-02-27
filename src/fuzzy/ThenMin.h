#ifndef LOGIQUEFLOUE_THENMIN_H
#define LOGIQUEFLOUE_THENMIN_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMin : public Then<T> {
    public:
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMin<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return 0;
    }
}


#endif //LOGIQUEFLOUE_THENMIN_H
