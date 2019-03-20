#ifndef LOGIQUEFLOUE_SLIDERCONTROLLER_H
#define LOGIQUEFLOUE_SLIDERCONTROLLER_H

#include "AbstractController.h"

namespace controller {

    class SliderController : public AbstractController {

    public:
        explicit SliderController(Model *_model, View *_view, Draftsman *_draftsman);
    };
}


#endif //LOGIQUEFLOUE_SLIDERCONTROLLER_H
