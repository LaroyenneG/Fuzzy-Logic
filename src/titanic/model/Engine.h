
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>
#include <exception>
#include "PhysicObject2D.h"

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION_SPEED 0.0
#define ENGINE_DEFAULT_ROTATION_ACCELERATION 0.0

#define ENGINE_CV_TO_WATT 735.5

#define ENGINE_BLADE_THRUST_MAGIC_NUMBER 1.42
#define ENGINE_BLADE_DRAG_MAGIC_NUMBER 0.1
#define ENGINE_BLADE_RADIUS_TO_WIDTH (2.0/3.0)

#define ENGINE_VALUE_ERROR_MSG "Engine invalid engine power"
#define ENGINE_DEFAULT_NAME "Engine"

namespace model {

    class Engine {

    private:
        double rotationAcceleration; // radian / s²
        double rotationSpeed;       // radian / s
        double desiredPower;               // [-1 - 1] %
        double power; // [-1 , 1] %

        const double friction;            // m / s
        const double propellerRadius;   // m
        const double propellerWeight;    // kg
        const double horsePower;  // hp
        const double maxRotationSpeed; // radian / s
        const double powerStep;  // % / s

        const unsigned short bladeNumber;

    protected:
        virtual double powerStepFunction(double _powerStep, double time, double _power, double _desiredPower) const;

        virtual double computeBladeThrust(double _rotationSpeed, double _propellerRadius) const;

        virtual double
        computeBladeRotationFriction(double _rotationSpeed, double _propellerRadius) const;

    public:

        explicit Engine(double _rotationAcceleration, double _rotationSpeed, double _desiredPower, double _friction,
                        double _propellerRadius, double _propellerWeight, double _horsePower, double _maxRotationSpeed,
                        double _powerStep, double _power, unsigned short _bladeNumber);

        explicit Engine(double _propellerRadius, double _propellerWeight, double _horsePower,
                        double _maxRotationSpeed,
                        double _friction, double _powerStep, unsigned short _bladeNumber);

        double getRotationSpeed() const;

        double getRotationFriction() const;

        double getMomentOfInercia() const;

        double computePropulsionStrength() const; // N

        void nextRotation(double time);

        void nexTime(double time);

        void nextPower(double time);

        virtual double getPropellerWidth() const;

        double getPower() const;

        virtual std::string getName() const;

        virtual void setPower(double value);

        virtual ~Engine() = default;

        double getHorsePower();

        virtual void resetToDefault();
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
