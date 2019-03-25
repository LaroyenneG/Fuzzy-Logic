

#include "AlternativeMachine.h"

namespace model {

    AlternativeMachine::AlternativeMachine()
            : Engine(ALTERNATIVE_DEFAULT_PROPELLER_DIAMETER, ALTERNATIVE_DEFAULT_PROPELLER_WEIGHT,
                     ALTERNATIVE_DEFAULT_MAX_POWER, ALTERNATIVE_DEFAULT_MAX_SPEED, ENGINE_DEFAULT_FRICTION,
                     ALTERNATIVE_DEFAULT_BLADE_NUMBER) {

    }

    std::string AlternativeMachine::getName() const {
        return std::string(ALTERNATIVE_DEFAULT_ENGINE_NAME);
    }
}