#include <cmath>
#include <stdexcept>
#include "Engine.h"
#include "Titanic.h"

namespace model {

    Engine::Engine(double _rotationAcceleration, double _rotationSpeed, double _desiredPower, double _friction,
                   double _propellerRadius, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                   double _powerStep, double _power, unsigned short _bladeNumber)
            : rotationAcceleration(_rotationAcceleration), rotationSpeed(_rotationSpeed), desiredPower(_desiredPower),
              power(_power),
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
                     _horsePower, _maxRotationSpeed, _powerStep, ENGINE_DEFAULT_POWER, _bladeNumber) {

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

        if (value < ENGINE_MIN_POWER || value > ENGINE_MAX_POWER) {
            throw std::out_of_range(ENGINE_VALUE_ERROR_MSG);
        }

        desiredPower = value;
    }

    std::string Engine::getName() const {
        return std::string(ENGINE_DEFAULT_NAME);
    }

    void Engine::nexTime(double time) {

        nextPower(time);

        double torque = (fabs(rotationSpeed) >= 1) ?
                        getHorsePower() * ENGINE_CV_TO_WATT / fabs(rotationSpeed)
                                                   :
                        getHorsePower() * ENGINE_CV_TO_WATT;

        const double propellerRotationFriction =
                computeBladeRotationFriction(rotationSpeed, propellerRadius) * bladeNumber;

        rotationAcceleration = torque / getMomentOfInercia() + propellerRotationFriction + getRotationFriction();

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

        double value = 0.0;

        if (fabs(_desiredPower) < fabs(_power) && _desiredPower < _power) {
            value = _powerStep;
        } else {
            value = _powerStep * time;
        }

        return value;
    }

    double Engine::getHorsePower() {

        return power * horsePower;
    }

    double Engine::computeBladeThrust(double _rotationSpeed, double _propellerRadius) const {

        static const unsigned int SAMPLING = 1000;
        static const double RESULTANT_COEFFICIENT = ENGINE_BLADE_THRUST_MAGIC_NUMBER;

        const double step = _propellerRadius / SAMPLING;
        const double widthPropeller = getPropellerWidth();

        double thrust = 0.0;

        double a = 0.0;
        double b = step;

        while (b < _propellerRadius) {

            double length = (a + b) / 2.0;

            double waterSpeed = _rotationSpeed * length;

            double surface = (b - a) / 2.0 * widthPropeller;

            double thrustValue = 0.5 * SEA_M_VOL * surface * RESULTANT_COEFFICIENT * waterSpeed * waterSpeed;

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

    double
    Engine::computeBladeRotationFriction(double _rotationSpeed, double _propellerRadius) const {

        static const unsigned int SAMPLING = 1000;
        static const double DRAG_COEFFICIENT = ENGINE_BLADE_DRAG_MAGIC_NUMBER;

        const double moment = getMomentOfInercia();
        const double step = _propellerRadius / SAMPLING;
        const double widthPropeller = getPropellerWidth();
        const double direction = (_rotationSpeed > 0) ? -1 : 1;

        double rotationFriction = 0;

        double a = 0.0;
        double b = step;

        while (b < _propellerRadius) {

            double length = (a + b) / 2.0;

            double waterSpeed = _rotationSpeed * length;

            double surface = (b - a) / 2.0 * widthPropeller;

            double dragValue = 0.5 * SEA_M_VOL * surface * DRAG_COEFFICIENT * waterSpeed * waterSpeed;

            rotationFriction += dragValue * length / moment;

            a = b;
            b += step;
        }

        return rotationFriction * direction;
    }

    double Engine::getRotationFriction() const {

        return rotationSpeed * friction * -1.0;
    }

    double Engine::getMomentOfInercia() const {

        return 0.5 * propellerWeight * propellerRadius * propellerRadius;
    }

    double Engine::getPropellerWidth() const {

        return propellerRadius * ENGINE_BLADE_RADIUS_TO_WIDTH;
    }

    void Engine::reachPower(double value) {

        static const unsigned int NB_LOOP = 1000;

        setPower(value);

        for (unsigned int i = 0; i < NB_LOOP; i++) {
            nexTime(1);
        }
    }
}
