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
        explicit NaryExpressionModel(NaryExpression<T> *_nOperator, const std::vector<Expression<T> *> &_operands);

        explicit NaryExpressionModel(NaryExpression<T> *_nOperator);

        explicit NaryExpressionModel();

        ~NaryExpressionModel();

        T evaluate(const std::vector<Expression<T> *> &_operands) const override;

        T evaluate() const override;

        unsigned long size() const;

        const NaryExpression<T> *getOperator() const;

        NaryExpression<T> *getOperator();
    };


    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel() : NaryExpressionModel(nullptr) {

    }

    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T> *_nOperator,
                                                const std::vector<Expression<T> *> &_operands)
            : operands(_operands), nOperator(_nOperator) {
    }

    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T> *_nOperator)
            : NaryExpressionModel(nullptr, _nOperator) {
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
    const NaryExpression<T> *NaryExpressionModel<T>::getOperator() const {

        return nOperator;
    }

    template<typename T>
    NaryExpression<T> *NaryExpressionModel<T>::getOperator() {

        return nOperator;
    }
}


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
