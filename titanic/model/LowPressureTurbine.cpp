
#include "LowPressureTurbine.h"


namespace model {
    LowPressureTurbine::LowPressureTurbine(const std::string &_name, double _propellerDiameter, double _propellerWeight)
            : Engine(_name, _propellerDiameter, _propellerWeight, TURBINE_DEFAULT_PROPELLER_MAX_POWER) {
    }

    LowPressureTurbine::LowPressureTurbine()
            : LowPressureTurbine(std::string(TURBINE_DEFAULT_ENGINE_NAME), TURBINE_DEFAULT_PROPELLER_DIAMETER,
                                 TURBINE_DEFAULT_PROPELLER_WEIGHT) {
    }
}