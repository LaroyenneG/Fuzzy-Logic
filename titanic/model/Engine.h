
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>
#include <exception>

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION 0.0
#define ENGINE_DEFAULT_FRICTION 0.0

#define ENGINE_VALUE_ERROR_MSG "Engine invalid engine power"

namespace model {

    class Engine {

    private:
        double rotationSpeed;       // radian / s
        double power;               // [-1 - 1] %

        const double friction;            // m / s
        const double propellerDiameter;   // m
        const double propellerWeight;     // kg
        const double maxPower;  // cv

    public:

        explicit Engine(double _rotationSpeed, double _power, double _friction,
                        double _propellerDiameter, double _propellerWeight, double _maxPower);

        explicit Engine(double _propellerDiameter, double _propellerWeight, double _maxPower);

        double getRotationSpeed() const;

        double getPropulsionStrength() const;

        double getPower() const;

        virtual void setPower(double value);

        virtual ~Engine() = default;
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
