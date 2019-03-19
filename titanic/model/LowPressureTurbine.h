#ifndef LOGIQUEFLOUE_LOWPRESSURETURBINE_H
#define LOGIQUEFLOUE_LOWPRESSURETURBINE_H

#include <exception>

#include "Engine.h"

#define TURBINE_DEFAULT_ENGINE_NAME "Low pressure turbine"

#define TURBINE_DEFAULT_PROPELLER_DIAMETER 5.20
#define TURBINE_DEFAULT_PROPELLER_WEIGHT 22000
#define TURBINE_DEFAULT_PROPELLER_MAX_POWER 16000

namespace model {

    class LowPressureTurbine : public Engine {
    public:
        explicit LowPressureTurbine(const std::string &_name, double _propellerDiameter, double _propellerWeight);

        explicit LowPressureTurbine();

        void setPower(double value) override;

        ~LowPressureTurbine() override = default;
    };
}


#endif //LOGIQUEFLOUE_LOWPRESSURETURBINE_H
