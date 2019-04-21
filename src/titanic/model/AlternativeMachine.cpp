

#include "AlternativeMachine.h"

namespace model {

    AlternativeMachine::AlternativeMachine()
            : Engine(ALTERNATIVE_DEFAULT_PROPELLER_DIAMETER / 2.0, ALTERNATIVE_DEFAULT_PROPELLER_WEIGHT,
                     ALTERNATIVE_DEFAULT_MAX_POWER, ALTERNATIVE_DEFAULT_MAX_SPEED, ALTERNATIVE_DEFAULT_FRICTION,
                     ALTERNATIVE_DEFAULT_POWER_STEP, ALTERNATIVE_DEFAULT_BLADE_NUMBER) {

    }

    std::string AlternativeMachine::getName() const {
        return std::string(ALTERNATIVE_DEFAULT_ENGINE_NAME);
    }

    double
    AlternativeMachine::powerStepFunction(double _powerStep, double time, double _power, double _desiredPower) const {

        static const int SLEEP_NUMBER = 2;

        if (_power < _desiredPower && fabs(_power) < pow(10, -SLEEP_NUMBER)) {
            _powerStep /= pow(10, SLEEP_NUMBER);
        } else if (_power > _desiredPower && fabs(_power) < pow(10, -SLEEP_NUMBER)) {
            _powerStep /= pow(10, SLEEP_NUMBER);
        }

        return _powerStep * time;
    }
}