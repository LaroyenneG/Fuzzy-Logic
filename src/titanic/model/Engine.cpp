#include <cmath>
#include <stdexcept>
#include "Engine.h"
#include "Titanic.h"

namespace model {

    Engine::Engine(double _rotationAcceleration, double _rotationSpeed, double _desiredPower, double _friction,
                   double _propellerRadius, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                   double _powerStep, unsigned short _bladeNumber)
            : rotationAcceleration(_rotationAcceleration), rotationSpeed(_rotationSpeed), desiredPower(_desiredPower),
              power(0),
              friction(_friction),
              propellerRadius(_propellerRadius), propellerWeight(_propellerWeight), horsePower(_horsePower),
              maxRotationSpeed(_maxRotationSpeed), powerStep(_powerStep), bladeNumber(_bladeNumber) {

    }

    Engine::Engine(double _propellerRadius, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                   double _friction, double _powerStep, unsigned short _bladeNumber)
            : Engine(ENGINE_DEFAULT_ROTATION_ACCELERATION, ENGINE_DEFAULT_ROTATION_SPEED, ENGINE_DEFAULT_POWER,
                     _friction,
                     _propellerRadius,
                     _propellerWeight,
                     _horsePower, _maxRotationSpeed, _powerStep, _bladeNumber) {

    }

    double Engine::getRotationSpeed() const {
        return rotationSpeed;
    }

    double Engine::computePropulsionStrength() const {

        double direction = (rotationSpeed < 0) ? -1.0 : 1.0;

        return direction * computeBladeThrust(rotationSpeed, propellerRadius) * bladeNumber;
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

        const double momentOfInertia = 0.5 * propellerWeight * propellerRadius * propellerRadius;

        double torque = (fabs(rotationSpeed) >= 1) ?
                        getHorsePower() * ENGINE_CV_TO_WATT / fabs(rotationSpeed)
                                                   :
                        getHorsePower() * ENGINE_CV_TO_WATT;

        double rotationFriction = -rotationSpeed * bladeNumber * propellerRadius * friction / propellerWeight;

        rotationAcceleration = torque / momentOfInertia + rotationFriction;

        nextRotation(time);
    }

    void Engine::nextRotation(double time) {

        rotationSpeed += rotationAcceleration * time;
    }

    void Engine::nextPower(double time) {

        double step = powerStepFunction(powerStep, time, power, desiredPower);

        if (power < desiredPower) {
            power = (power + step < desiredPower) ? power + step : desiredPower;
        }
        if (power > desiredPower) {
            power = (power - step > desiredPower) ? power - step : desiredPower;
        }
    }

    double Engine::powerStepFunction(double _powerStep, double time, double _power, double _desiredPower) const {

        return _powerStep * time;
    }

    double Engine::getHorsePower() {

        return power * horsePower;
    }

    double Engine::computeBladeThrust(double _rotationSpeed, double _propellerRadius) const {

        static const unsigned int SAMPLING = 10000;
        static const double THRUST_COEFFICIENT = ENGINE_BLADE_THRUST_MAGIC_NUMBER;

        const double step = _propellerRadius / SAMPLING;
        const double width = propellerRadius * 2.0 / 3.0;

        double thrust = 0.0;

        double a = 0.0;
        double b = step;


        while (b < propellerRadius) {

            double length = (a + b) / 2.0;

            double waterSpeed = _rotationSpeed * length;

            double surface = (b - a) / 2.0 * width;

            double thrustValue = 0.5 * SEA_M_VOL * surface * THRUST_COEFFICIENT * waterSpeed * waterSpeed;

            thrust += thrustValue;

            a = b;
            b += step;
        }

        return thrust;
    }

    void Engine::resetToDefault() {

        rotationSpeed = ENGINE_DEFAULT_ROTATION_SPEED;
        rotationAcceleration = ENGINE_DEFAULT_ROTATION_ACCELERATION;
        power = ENGINE_DEFAULT_POWER;
    }
}
