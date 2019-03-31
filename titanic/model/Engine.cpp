#include <cmath>
#include <stdexcept>
#include "Engine.h"

namespace model {

    Engine::Engine(double _rotationAcceleration, double _rotationSpeed, double _desiredPower, double _friction,
                   double _propellerDiameter, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                   double _powerStep, unsigned short _bladeNumber)
            : rotationAcceleration(_rotationAcceleration), rotationSpeed(_rotationSpeed), desiredPower(_desiredPower),
              power(0),
              friction(_friction),
              propellerDiameter(_propellerDiameter), propellerWeight(_propellerWeight), horsePower(_horsePower),
              maxRotationSpeed(_maxRotationSpeed), powerStep(_powerStep), bladeNumber(_bladeNumber) {

    }

    Engine::Engine(double _propellerDiameter, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                   double _friction, double _powerStep, unsigned short _bladeNumber)
            : Engine(ENGINE_DEFAULT_ROTATION_ACCELERATION, ENGINE_DEFAULT_ROTATION_SPEED, ENGINE_DEFAULT_POWER,
                     _friction,
                     _propellerDiameter,
                     _propellerWeight,
                     _horsePower, _maxRotationSpeed, _powerStep, _bladeNumber) {

    }

    double Engine::getRotationSpeed() const {
        return rotationSpeed;
    }

    double Engine::computePropulsionStrength() const {

        return rotationSpeed * propellerDiameter / 2.0 * ENGINE_BLADE_LIFT_MAGIC_NUMBER * bladeNumber;
    }

    double Engine::getPower() const {
        return power;
    }

    void Engine::setPower(double value) {

        if (value < -1.0 || value > 1.0) {
            throw std::out_of_range(ENGINE_VALUE_ERROR_MSG);
        }

        desiredPower = value;
    }

    std::string Engine::getName() const {
        return std::string(ENGINE_DEFAULT_NAME);
    }

    void Engine::nexTime(double time) {

        nextPower(time);

        const double momentOfInertia = 0.5 * propellerWeight * (propellerDiameter / 2.0) * (propellerDiameter / 2.0);

        double torque = (rotationSpeed != 0) ?
                        getHorsePower() * ENGINE_CV_TO_WATT / fabs(rotationSpeed)
                                             :
                        getHorsePower() * ENGINE_CV_TO_WATT;

        rotationAcceleration =
                torque / momentOfInertia - rotationSpeed * friction / momentOfInertia;

        nextRotation(time);
    }

    void Engine::nextRotation(double time) {

        rotationSpeed += rotationAcceleration * time;
    }

    void Engine::nextPower(double time) {

        double step = powerFunction(powerStep, time);

        if (power < desiredPower) {
            power = (power + step < desiredPower) ? power + step : desiredPower;
        }
        if (power > desiredPower) {
            power = (power - step > desiredPower) ? power - step : desiredPower;
        }
    }

    double Engine::powerFunction(double _powerStep, double time) const {
        return _powerStep * time + 1.0;
    }

    double Engine::getHorsePower() {

        return power * horsePower;
    }
}
