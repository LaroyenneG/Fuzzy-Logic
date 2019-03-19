
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION 0.0
#define ENGINE_DEFAULT_FRICTION 0.0

namespace model {

    class Engine {

    private:
        const std::string name;

        double rotationSpeed;       // radian / s
        double power;               // [0 - 1] %

        const double friction;            // m / s
        const double propellerDiameter;   // m
        const double propellerWeight;     // kg
        const double maxPower;  // cv

    public:

        explicit Engine(const std::string &_name, double _rotationSpeed, double _power, double _friction,
                        double _propellerDiameter, double _propellerWeight, double _maxPower);

        explicit Engine(const std::string &_name, double _propellerDiameter, double _propellerWeight, double _maxPower);

        double getRotationSpeed() const;

        const std::string &getName() const;

        double getPropulsionStrength() const;

        double getPower() const;

        void setPower(double value);
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
