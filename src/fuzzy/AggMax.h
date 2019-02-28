#ifndef LOGIQUEFLOUE_AGGMAX_H
#define LOGIQUEFLOUE_AGGMAX_H

#include "Agg.h"
#include "Expression.h"

namespace fuzzy {
    template<typename T>
    class AggMax : public Agg<T> {
    public :
        T evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const override;
    };

    template<typename T>
    T AggMax<T>::evaluate(const core::Expression<T> *left, const core::Expression<T> *right) const {
        return 0;
    }
}
#endif //LOGIQUEFLOUE_AGGMAX_H
