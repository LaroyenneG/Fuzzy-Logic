
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>
#include <exception>
#include "PhysicObject2D.h"

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION_SPEED 0.0
#define ENGINE_DEFAULT_ROTATION_ACCELERATION 0.0

#define ENGINE_CV_TO_WATT 735.5

#define ENGINE_BLADE_LIFT_MAGIC_NUMBER 3000.0 // N.r / (rad / s)

#define ENGINE_VALUE_ERROR_MSG "Engine invalid engine power"
#define ENGINE_DEFAULT_NAME "Engine"

namespace model {

    class Engine {

    private:
        double rotationAcceleration; // radian / s²
        double rotationSpeed;       // radian / s
        double desiredPower;               // [-1 - 1] %
        double power; // [-1 - 1] %

        const double friction;            // m / s
        const double propellerDiameter;   // m
        const double propellerWeight;     // kg
        const double horsePower;  // hp
        const double maxRotationSpeed; // radian / s
        const double powerStep;  // % / s

        const unsigned short bladeNumber;

    protected:
        virtual double powerFunction(double _powerStep, double time) const;

    public:

        explicit Engine(double _rotationAcceleration, double _rotationSpeed, double _desiredPower, double _friction,
                        double _propellerDiameter, double _propellerWeight, double _horsePower,
                        double _maxRotationSpeed,
                        double _powerStep, unsigned short _bladeNumber);

        explicit Engine(double _propellerDiameter, double _propellerWeight, double _horsePower,
                        double _maxRotationSpeed,
                        double _friction, double _powerStep, unsigned short _bladeNumber);

        double getRotationSpeed() const;

        double computePropulsionStrength() const; // N

        void nextRotation(double time);

        void nexTime(double time);

        void nextPower(double time);

        double getPower() const;

        virtual std::string getName() const;

        virtual void setPower(double value);

        virtual ~Engine() = default;

        double getHorsePower();
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
