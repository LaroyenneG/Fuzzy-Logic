
#include <stdexcept>
#include "LowPressureTurbine.h"


namespace model {
    LowPressureTurbine::LowPressureTurbine(double _propellerDiameter, double _propellerWeight)
            : Engine(_propellerDiameter, _propellerWeight, TURBINE_DEFAULT_PROPELLER_MAX_POWER) {
    }

    LowPressureTurbine::LowPressureTurbine()
            : LowPressureTurbine(TURBINE_DEFAULT_PROPELLER_DIAMETER,
                                 TURBINE_DEFAULT_PROPELLER_WEIGHT) {
    }

    void LowPressureTurbine::setPower(double value) {

        if (value < 0.0) {
            throw std::out_of_range(ENGINE_VALUE_ERROR_MSG);
        }

        Engine::setPower(value);
    }

    std::string LowPressureTurbine::getName() const {
        return std::string(TURBINE_DEFAULT_ENGINE_NAME);
    }
}