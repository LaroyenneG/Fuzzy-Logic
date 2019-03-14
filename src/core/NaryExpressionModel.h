#ifndef LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H

#include <exception>

#include "NaryExpression.h"
#include "OperatorNullException.h"
#include "OperandNullException.h"

namespace core {

    template<typename T>
    class NaryExpressionModel : public NaryExpression<T>, public Expression<T> {

    private:
        std::vector<Expression<T> *> operands;
        NaryExpression<T> *nOperator;

    public:
        explicit NaryExpressionModel(NaryExpression<T> *_nOperator, std::vector<Expression<T> *> &_operands);

        explicit NaryExpressionModel(NaryExpression<T> *_nOperator);

        ~NaryExpressionModel();

        T evaluate(const std::vector<Expression<T> *> &_operands) const override;

        T evaluate() const override;

        unsigned long size() const;
    };


    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T> *_nOperator, std::vector<Expression<T> *> &_operands)
            : operands(_operands), nOperator(_nOperator) {
    }

    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T> *_nOperator)
            : operands(0), nOperator(_nOperator) {
    }

    template<typename T>
    NaryExpressionModel<T>::~NaryExpressionModel() = default;

    template<typename T>
    unsigned long NaryExpressionModel<T>::size() const {
        return operands.size();
    }

    template<typename T>
    T NaryExpressionModel<T>::evaluate(const std::vector<Expression<T> *> &_operands) const {

        if (nOperator == nullptr) {
            throw exception::OperatorNullException();
        }

        return nOperator->evaluate(_operands);
    }

    template<typename T>
    T NaryExpressionModel<T>::evaluate() const {

        for (auto operand : operands) {
            if (operand == nullptr) {
                throw exception::OperandNullException();
            }
        }

        return evaluate(operands);
    }
}


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
