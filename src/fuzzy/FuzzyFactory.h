#ifndef LOGIQUEFLOUE_FUZZYFACTORY_H
#define LOGIQUEFLOUE_FUZZYFACTORY_H

#include <UnaryExpression.h>
#include <BinaryExpression.h>
#include "ExpressionFactory.h"

namespace fuzzy {

    template<typename T>
    class FuzzyFactory : public core::ExpressionFactory<T> {

    public:
    };
}


#endif //LOGIQUEFLOUE_FUZZYFACTORY_H
