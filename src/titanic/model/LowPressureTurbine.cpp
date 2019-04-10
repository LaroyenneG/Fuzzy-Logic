
#include <stdexcept>
#include "LowPressureTurbine.h"


namespace model {


    LowPressureTurbine::LowPressureTurbine()
            : Engine(TURBINE_DEFAULT_PROPELLER_DIAMETER / 2.0, TURBINE_DEFAULT_PROPELLER_WEIGHT,
                     TURBINE_DEFAULT_PROPELLER_MAX_POWER, TURBINE_DEFAULT_MAX_SPEED, TURBINE_DEFAULT_FRICTION,
                     TURBINE_DEFAULT_POWER_STEP, TURBINE_DEFAULT_BLADE_NUMBER) {
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

    double
    LowPressureTurbine::powerStepFunction(double _powerStep, double time, double _power, double _desiredPower) const {

        double value = _powerStep * time;

        /*
        if (fabs(_power) <= 0.5) {
            value /= 10.0;
        }
         */

        return value;
    }
}