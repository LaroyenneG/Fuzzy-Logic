
#include "Engine.h"

model::Engine::Engine(const std::string &_name, double _propellerDiameter, double _propellerWeight)
        : name(_name), rotationSpeed(DEFAULT_ROTATION), power(DEFAULT_POWER), friction(DEFAULT_FRICTION),
          propellerDiameter(_propellerDiameter), propellerWeight(_propellerWeight) {

}

double model::Engine::getRotationSpeed() const {
    return rotationSpeed;
}

const std::string &model::Engine::getName() const {
    return name;
}

double model::Engine::getPropulsionStrength() const {
    return 0;
}

double model::Engine::getPower() const {
    return power;
}

void model::Engine::setPower(double value) {
    power = value;
}
