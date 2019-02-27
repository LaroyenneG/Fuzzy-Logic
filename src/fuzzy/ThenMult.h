#ifndef LOGIQUEFLOUE_THENMULT_H
#define LOGIQUEFLOUE_THENMULT_H

#include "Then.h"

namespace fuzzy {

    template<typename T>
    class ThenMult : public Then<T> {

    public:
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T ThenMult<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return 0;
    }
}

#endif //LOGIQUEFLOUE_THENMULT_H
