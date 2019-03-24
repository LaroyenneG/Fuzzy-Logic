
#include <stdexcept>
#include "LowPressureTurbine.h"


namespace model {


    LowPressureTurbine::LowPressureTurbine()
            : Engine(TURBINE_DEFAULT_PROPELLER_DIAMETER, TURBINE_DEFAULT_PROPELLER_WEIGHT,
                     TURBINE_DEFAULT_PROPELLER_MAX_POWER, TURBINE_DEFAULT_MAX_SPEED, TURBINE_DEFAULT_FRICTION) {
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