#ifndef LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
#define LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H

#include "NaryExpression.h"

namespace core {

    template<typename T>
    class NaryShadowExpression : public NaryExpression<T> {

    private:
        NaryExpression<T> *target;

    public:
        explicit NaryShadowExpression(NaryExpression<T> *_target);
    };

    template<typename T>
    NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T> *_target) : target(_target) {
    }
}


#endif //LOGIQUEFLOUE_NARYSHADOWEXPRESSION_H
