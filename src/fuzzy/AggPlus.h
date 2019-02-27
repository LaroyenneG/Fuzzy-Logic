#ifndef LOGIQUEFLOUE_AGGPLUS_H
#define LOGIQUEFLOUE_AGGPLUS_H

namespace fuzzy {

    template<typename T>
    class AggPlus : public Agg<T> {
    public :
        T evaluate(const Expression <T> *left, const Expression <T> *right) const override;
    };

    template<typename T>
    T AggPlus<T>::evaluate(const Expression <T> *left, const Expression <T> *right) const {
        return 0;
    }
}
#endif //LOGIQUEFLOUE_AGGPLUS_H
