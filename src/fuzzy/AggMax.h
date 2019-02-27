#ifndef LOGIQUEFLOUE_AGGMAX_H
#define LOGIQUEFLOUE_AGGMAX_H

namespace fuzzy {


    template<typename T>
    class AggMax : public Agg<T> {
    public :
        T evaluate(const Expression <T> *left, const Expression <T> *right) const override;
    };

    template<typename T>
    T AggMax<T>::evaluate(const Expression <T> *left, const Expression <T> *right) const {
        return 0;
    }
}
#endif //LOGIQUEFLOUE_AGGMAX_H
