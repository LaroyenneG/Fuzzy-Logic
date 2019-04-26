
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

        static const int SLEEP_NUMBER = 7;

        if (_power < _desiredPower && _desiredPower < TURBINE_DEFAULT_MINIMUM_POWER_ACTIVATION) {
            _powerStep = 0.0;
        }

        if (_power < _desiredPower && _power < pow(10, -SLEEP_NUMBER)) {
            _powerStep /= pow(10, SLEEP_NUMBER);
        }

        return Engine::powerStepFunction(_powerStep, time, _power, _desiredPower);
    }
}