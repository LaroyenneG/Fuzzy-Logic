#ifndef LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H

#include <exception>

#include "NaryExpression.h"
#include "OperatorNullException.h"
#include "OperandNullException.h"

namespace fuzzylogic::core {

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

        bool isValue() const override;
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
            throw fuzzylogic::exception::OperatorNullException();
        }

        return nOperator->evaluate(_operands);
    }

    template<typename T>
    T NaryExpressionModel<T>::evaluate() const {

        for (auto operand : operands) {
            if (operand == nullptr) {
                throw fuzzylogic::exception::OperandNullException();
            }
        }

        return evaluate(operands);
    }

    template<typename T>
    bool NaryExpressionModel<T>::isValue() const {
        return false;
    }
}


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
