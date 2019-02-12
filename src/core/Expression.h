#ifndef LOGIQUEFLOUE_EXPRESSION_H
#define LOGIQUEFLOUE_EXPRESSION_H

namespace core {
    template<typename T>
    class Expression {
    public:
        virtual T evaluate() const = 0;
    };
}


#endif //LOGIQUEFLOUE_EXPRESSION_H
