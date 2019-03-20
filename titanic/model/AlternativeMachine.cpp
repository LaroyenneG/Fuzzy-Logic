

#include "AlternativeMachine.h"

namespace model {

    AlternativeMachine::AlternativeMachine(double _propellerDiameter, double _propellerWeight)
            : Engine(_propellerDiameter, _propellerWeight, ALTERNATIVE_DEFAULT_MAX_POWER) {

    }

    AlternativeMachine::AlternativeMachine()
            : AlternativeMachine(ALTERNATIVE_DEFAULT_PROPELLER_DIAMETER,
                                 ALTERNATIVE_DEFAULT_PROPELLER_WEIGHT) {

    }

    std::string AlternativeMachine::getName() const {
        return std::string(ALTERNATIVE_DEFAULT_ENGINE_NAME);
    }
}