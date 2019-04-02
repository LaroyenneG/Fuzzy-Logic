#ifndef LOGIQUEFLOUE_EXPRESSION_H
#define LOGIQUEFLOUE_EXPRESSION_H

namespace core {

    template<typename T>
    class Expression {

    public:
        const static T ZERO;
        const static T ONE;
        const static T TWO;

    public:
        virtual T evaluate() const = 0;

        virtual ~Expression() = default;

        virtual bool isValue() const = 0;
    };


    template<typename T>
    const T Expression<T>::ZERO(0);

    template<typename T>
    const T Expression<T>::ONE(1);

    template<typename T>
    const T Expression<T>::TWO(2);
}


#endif //LOGIQUEFLOUE_EXPRESSION_H
