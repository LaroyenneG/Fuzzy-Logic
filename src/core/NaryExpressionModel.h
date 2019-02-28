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
        const Expression<T> **operands;
        const NaryExpression<T> *nOperator;

        static unsigned int elementCounter(const void **elements);

        static void **allocate(unsigned int size);

    public:
        explicit NaryExpressionModel(const NaryExpression<T> *_nOperator, const Expression<T> **_operands);

        explicit NaryExpressionModel(const NaryExpression<T> *_nOperator);

        ~NaryExpressionModel();

        T evaluate(const Expression<T> **_operands) const override;

        T evaluate() const override;

        unsigned int size() const;
    };


    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(const NaryExpression<T> *_nOperator, const Expression<T> **_operands)
            : operands(allocate(elementCounter(_operands))), nOperator(_nOperator) {

        unsigned int index = 0;

        while (_operands[index] != nullptr) {
            operands[index] = _operands[index];
            index++;
        }
    }

    template<typename T>
    NaryExpressionModel<T>::NaryExpressionModel(const NaryExpression<T> *_nOperator)
            : operands(nullptr), nOperator(_nOperator) {
    }

    template<typename T>
    NaryExpressionModel<T>::~NaryExpressionModel() {
        delete[] operands;
    }

    template<typename T>
    unsigned int NaryExpressionModel<T>::size() const {
        return elementCounter(operands);
    }

    template<typename T>
    T NaryExpressionModel<T>::evaluate(const Expression<T> **_operands) const {

        if (nOperator == nullptr) {
            throw exception::OperatorNullException();
        }

        return nOperator->evaluate(_operands);
    }

    template<typename T>
    T NaryExpressionModel<T>::evaluate() const {

        if (operands == nullptr) {
            throw exception::OperandNullException();
        }

        return evaluate(operands);
    }

    /*
     * static functions
     */
    template<typename T>
    unsigned int NaryExpressionModel<T>::elementCounter(const void **elements) {

        unsigned int index = 0;

        while (elements[index] != nullptr) {
            index++;
        }

        return index;
    }

    template<typename T>
    void **NaryExpressionModel<T>::allocate(unsigned int size) {

        void **table = new void *[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }

        return table;
    }
}


#endif //LOGIQUEFLOUE_NARYEXPRESSIONMODEL_H
