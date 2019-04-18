#ifndef LOGIQUEFLOUE_EXPRESSION_H
#define LOGIQUEFLOUE_EXPRESSION_H

#include "CoreObject.h"

namespace fuzzylogic::core {

    template<typename T>
    class Expression : public CoreObject<T> {

    public:
        virtual T evaluate() const = 0;

        virtual ~Expression() = default;
    };
}


#endif //LOGIQUEFLOUE_EXPRESSION_H
