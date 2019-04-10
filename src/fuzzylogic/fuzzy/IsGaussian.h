#ifndef LOGIQUEFLOUE_ISGAUSSIAN_H
#define LOGIQUEFLOUE_ISGAUSSIAN_H

#include "Is.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class IsGaussian : public Is<T> {
    private:
        T mean;
        T variance;


    public:
        explicit IsGaussian(const T &_mean, const T &_variance);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getMean() const;

        const T &getVariance() const;

        void setMean(const T &_mean);

        void setVariance(const T &_variance);

    };

    template<typename T>
    IsGaussian<T>::IsGaussian(const T &_mean, const T &_variance) : mean(_mean), variance(_variance) {

    }

    template<typename T>
    T IsGaussian<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        T value = expression->evaluate();

        T result(std::exp((-0.5 * pow(value - mean, 2)) / pow(variance, 2)));

        return result;
    }

    template<typename T>
    const T &IsGaussian<T>::getMean() const {
        return mean;
    }

    template<typename T>
    const T &IsGaussian<T>::getVariance() const {
        return variance;
    }

    template<typename T>
    void IsGaussian<T>::setMean(const T &_mean) {
        mean = _mean;
    }

    template<typename T>
    void IsGaussian<T>::setVariance(const T &_variance) {
        variance = _variance;
    }


}
#endif //LOGIQUEFLOUE_ISGAUSSIAN_H
