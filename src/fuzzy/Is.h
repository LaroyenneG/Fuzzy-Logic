#ifndef LOGIQUEFLOUE_IS_H
#define LOGIQUEFLOUE_IS_H

#include "UnaryExpression.h"

namespace fuzzy {

    template<typename T>
    class Is : public core::UnaryExpression<T> {
    };
}

#endif //LOGIQUEFLOUE_IS_H
