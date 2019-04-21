#ifndef LOGIQUEFLOUE_NARYEXPRESSION_H
#define LOGIQUEFLOUE_NARYEXPRESSION_H

#include <vector>
#include "Expression.h"
#include "CoreObject.h"

namespace fuzzylogic::core {

    template<typename T>
    class NaryExpression : public CoreObject<T> {

    public:
        virtual T evaluate(const std::vector<Expression < T> *> &operands) const = 0;

        virtual ~NaryExpression() = default;
    };
}

#endif //LOGIQUEFLOUE_NARYEXPRESSION_H
