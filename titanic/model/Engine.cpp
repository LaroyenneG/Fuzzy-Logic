#include <cmath>
#include <stdexcept>
#include "Engine.h"

namespace model {

    Engine::Engine(double _rotationAcceleration, double _rotationSpeed, double _power, double _friction,
                   double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed)
            : rotationAcceleration(_rotationAcceleration), rotationSpeed(_rotationSpeed), power(_power),
              friction(_friction),
              propellerDiameter(_propellerDiameter), propellerWeight(_propellerWeight), maxPower(_maxPower),
              maxRotationSpeed(_maxRotationSpeed) {

    }

    Engine::Engine(double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed)
            : Engine(ENGINE_DEFAULT_ROTATION_ACCELERATION, ENGINE_DEFAULT_ROTATION_SPEED, ENGINE_DEFAULT_POWER,
                     ENGINE_DEFAULT_FRICTION,
                     _propellerDiameter,
                     _propellerWeight,
                     _maxPower, _maxRotationSpeed) {

    }

    double Engine::getRotationSpeed() const {
        return rotationSpeed;
    }

    double Engine::getPropulsionStrength() const {

        return ENGINE_MAGIC_NUMBER * maxPower * rotationSpeed / maxRotationSpeed;
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

        rotationAcceleration = power - rotationSpeed * 0.1;

        nextRotation(time);
    }

    void Engine::nextRotation(double time) {

        rotationSpeed += rotationAcceleration * time;

        if (rotationSpeed > maxRotationSpeed) {
            rotationSpeed = maxRotationSpeed;
        }
        if (rotationSpeed < -maxRotationSpeed) {
            rotationSpeed = -maxRotationSpeed;
        }
    }
}
