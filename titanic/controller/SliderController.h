#ifndef LOGIQUEFLOUE_SLIDERCONTROLLER_H
#define LOGIQUEFLOUE_SLIDERCONTROLLER_H

#include "AbstractController.h"

namespace controller {

    class SliderController : public AbstractController {

    Q_OBJECT

    public:
        explicit SliderController(Model *_model, View *_view, Draftsman *_draftsman);

        ~SliderController() override = default;

    public slots:

        void machinePowerSliderValueChanged(int value);

        void helmSliderValueChanged(int value);
    };
}


#endif //LOGIQUEFLOUE_SLIDERCONTROLLER_H
