
#ifndef LOGIQUEFLOUE_ALTERNATIVEMACHINE_H
#define LOGIQUEFLOUE_ALTERNATIVEMACHINE_H

#include "Engine.h"

#define ALTERNATIVE_DEFAULT_ENGINE_NAME "Alternative machine"

#define ALTERNATIVE_DEFAULT_PROPELLER_DIAMETER 7.20
#define ALTERNATIVE_DEFAULT_PROPELLER_WEIGHT 38000
#define ALTERNATIVE_DEFAULT_MAX_POWER 15000

namespace model {

    class AlternativeMachine : public Engine {
    public:
        explicit AlternativeMachine(const std::string &_name, double _propellerDiameter,
                                    double _propellerWeight);

        explicit AlternativeMachine();

        ~AlternativeMachine() = default;
    };
}

#endif //LOGIQUEFLOUE_ALTERNATIVEMACHINE_H
