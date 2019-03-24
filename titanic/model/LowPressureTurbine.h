#ifndef LOGIQUEFLOUE_LOWPRESSURETURBINE_H
#define LOGIQUEFLOUE_LOWPRESSURETURBINE_H

#include <exception>

#include "Engine.h"

#define TURBINE_DEFAULT_ENGINE_NAME "Low pressure turbine"

#define TURBINE_DEFAULT_PROPELLER_DIAMETER 5.20
#define TURBINE_DEFAULT_PROPELLER_WEIGHT 22000
#define TURBINE_DEFAULT_PROPELLER_MAX_POWER 16000  // CV
#define TURBINE_DEFAULT_MAX_SPEED 167 * 0.10472
#define TURBINE_DEFAULT_FRICTION 0.9

namespace model {

    class LowPressureTurbine : public Engine {
    public:
        explicit LowPressureTurbine();

        void setPower(double value) override;

        std::string getName() const override;

        ~LowPressureTurbine() override = default;
    };
}


#endif //LOGIQUEFLOUE_LOWPRESSURETURBINE_H
