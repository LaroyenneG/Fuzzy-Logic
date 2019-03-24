
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>
#include <exception>

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION_SPEED 0.0
#define ENGINE_DEFAULT_ROTATION_ACCELERATION 0.0
#define ENGINE_DEFAULT_FRICTION 0.7

#define ENGINE_CV_TO_NEWTON_M_S 735.5

#define ENGINE_VALUE_ERROR_MSG "Engine invalid engine power"
#define ENGINE_DEFAULT_NAME "Engine"

namespace model {

    class Engine {

    private:
        double rotationAcceleration; // radian / s²
        double rotationSpeed;       // radian / s
        double power;               // [-1 - 1] %

        const double friction;            // m / s
        const double propellerDiameter;   // m
        const double propellerWeight;     // kg
        const double maxPower;  // cv
        const double maxRotationSpeed; // radian / s


    public:

        explicit Engine(double _rotationAcceleration, double _rotationSpeed, double _power, double _friction,
                        double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed);

        explicit Engine(double _propellerDiameter, double _propellerWeight, double _maxPower, double _maxRotationSpeed,
                        double _friction);

        double getRotationSpeed() const;

        double getPropulsionStrength() const; // N / S

        void nextRotation(double time);

        void nexTime(double time);

        double getPower() const;

        virtual std::string getName() const;

        virtual void setPower(double value);

        virtual ~Engine() = default;
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
