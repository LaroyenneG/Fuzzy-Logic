
#ifndef LOGIQUEFLOUE_ALTERNATIVEMACHINE_H
#define LOGIQUEFLOUE_ALTERNATIVEMACHINE_H

#include "Engine.h"

#define ALTERNATIVE_DEFAULT_ENGINE_NAME "Alternative machine"

#define ALTERNATIVE_DEFAULT_PROPELLER_DIAMETER 7.20
#define ALTERNATIVE_DEFAULT_PROPELLER_WEIGHT 38000
#define ALTERNATIVE_DEFAULT_MAX_POWER 15000  // CV
#define ALTERNATIVE_DEFAULT_MAX_SPEED 77 * 0.10472
#define ALTERNATIVE_DEFAULT_BLADE_NUMBER 3
#define ALTERNATIVE_DEFAULT_FRICTION 0.44
#define ALTERNATIVE_DEFAULT_POWER_STEP 0.05

namespace model {

    class AlternativeMachine : public Engine {

    protected:
        double powerStepFunction(double _powerStep, double time, double _power, double _desiredPower) const override;

    public:
        explicit AlternativeMachine();

        std::string getName() const override;

        ~AlternativeMachine() override = default;
    };
}

#endif //LOGIQUEFLOUE_ALTERNATIVEMACHINE_H
