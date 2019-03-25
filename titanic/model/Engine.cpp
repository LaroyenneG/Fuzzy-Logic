#include <cmath>
#include <stdexcept>
#include "Engine.h"

namespace model {

    Engine::Engine(double _rotationAcceleration, double _rotationSpeed, double _power, double _friction,
                   double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed,
                   unsigned short _bladeNumber)
            : rotationAcceleration(_rotationAcceleration), rotationSpeed(_rotationSpeed), power(_power),
              friction(_friction),
              propellerDiameter(_propellerDiameter), propellerWeight(_propellerWeight), maxPower(_maxPower),
              maxRotationSpeed(_maxRotationSpeed), bladeNumber(_bladeNumber) {

    }

    Engine::Engine(double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed,
                   double _friction, unsigned short _bladeNumber)
            : Engine(ENGINE_DEFAULT_ROTATION_ACCELERATION, ENGINE_DEFAULT_ROTATION_SPEED, ENGINE_DEFAULT_POWER,
                     _friction,
                     _propellerDiameter,
                     _propellerWeight,
                     _maxPower, _maxRotationSpeed, _bladeNumber) {

    }

    double Engine::getRotationSpeed() const {
        return rotationSpeed;
    }

    double Engine::getPropulsionStrength() const {

        return ENGINE_CV_TO_NEWTON_M_S * maxPower * rotationSpeed / maxRotationSpeed;
    }

    double Engine::getPower() const {
        return power;
    }

    void Engine::setPower(double value) {

        if (value < -1.0 || value > 1.0) {
            throw std::out_of_range(ENGINE_VALUE_ERROR_MSG);
        }

        power = value;
    }

    std::string Engine::getName() const {
        return std::string(ENGINE_DEFAULT_NAME);
    }

    void Engine::nexTime(double time) {

        const double momentOfInertia = 0.5 * propellerWeight * (propellerDiameter / 2.0) * (propellerDiameter / 2.0);

        rotationAcceleration = ENGINE_CV_TO_NEWTON_M_S * time * power * maxPower / momentOfInertia
                               - rotationSpeed * friction * propellerDiameter * bladeNumber / propellerWeight;

        nextRotation(time);
    }

    void Engine::nextRotation(double time) {

        rotationSpeed += rotationAcceleration * time;
    }
}
