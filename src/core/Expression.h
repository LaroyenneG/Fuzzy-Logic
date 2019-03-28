#ifndef LOGIQUEFLOUE_EXPRESSION_H
#define LOGIQUEFLOUE_EXPRESSION_H

namespace core {
    template<typename T>
    class Expression {
    public:
        virtual T evaluate() const = 0;

        virtual ~Expression() = default;

        virtual bool isValue() const;
    };

    template<typename T>
    bool Expression<T>::isValue() const { return false; }
}


#endif //LOGIQUEFLOUE_EXPRESSION_H
