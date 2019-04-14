#ifndef LOGIQUEFLOUE_SUGENOCONCLUSION_H
#define LOGIQUEFLOUE_SUGENOCONCLUSION_H

#include <vector>
#include "NaryExpression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>

    class SugenoConclusion : public fuzzylogic::core::NaryExpression<T> {

    private:
        std::vector<T> coefficients;

    public:
        explicit SugenoConclusion() = default;

        explicit SugenoConclusion(const std::vector<T> &_coefficients);

        T evaluate(const std::vector<fuzzylogic::core::Expression<T> *> &operands) const override;

        const std::vector<T> &getCoefficients() const;

        void setCoefficients(const std::vector<T> &_coefficients);
    };

    template<typename T>
    SugenoConclusion<T>::SugenoConclusion(const std::vector<T> &_coefficients) : coefficients(_coefficients) {

    }

    template<typename T>
    T SugenoConclusion<T>::evaluate(const std::vector<fuzzylogic::core::Expression<T> *> &operands) const {

        T value(0);

        for (unsigned int i = 0; i < operands.size() && i < coefficients.size(); i++) {
            value += operands[i]->evaluate() * coefficients[i];
        }

        return value;
    }

    template<typename T>
    const std::vector<T> &SugenoConclusion<T>::getCoefficients() const {

        return coefficients;
    }

    template<typename T>
    void SugenoConclusion<T>::setCoefficients(const std::vector<T> &_coefficients) {
        coefficients = _coefficients;
    }
}

#endif //LOGIQUEFLOUE_SUGENOCONCLUSION_H
