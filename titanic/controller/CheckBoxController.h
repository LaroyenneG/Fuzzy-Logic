#ifndef LOGIQUEFLOUE_CONTROLER_H
#define LOGIQUEFLOUE_CONTROLER_H


#include "AbstractController.h"

namespace controller {

    class CheckBoxController : public AbstractController {

    public:
        explicit CheckBoxController() : AbstractController(nullptr, nullptr, nullptr) {}
    };
}

#endif //LOGIQUEFLOUE_CONTROLER_H
