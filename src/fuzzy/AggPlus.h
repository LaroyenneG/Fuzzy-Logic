#ifndef LOGIQUEFLOUE_AGGPLUS_H
#define LOGIQUEFLOUE_AGGPLUS_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy {
    template<typename T>
    class AggPlus : public Agg<T> {
    public :
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T AggPlus<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return 0;
    }
}
#endif //LOGIQUEFLOUE_AGGPLUS_H
