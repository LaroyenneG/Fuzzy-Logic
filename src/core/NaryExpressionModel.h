#ifndef LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H

#include <NaryExpression.h>

namespace core {

    template<typename T>
    class NaryExpressionModel : public NaryExpression<T>, public Expression<T> {

    private:
        Expression<T> **operands;

    public:
        explicit NaryExpressionModel(const Expression<T> **operands);

    };

    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(const Expression<T> **operands) {

    }
}


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
