

#include "Model.h"

namespace model {

    Model::Model(double _clock, double _timeAcceleration, double _visibility)
            : titanic(new Titanic()), iceberg(new Iceberg()), clockStep(_clock), timeAcceleration(_timeAcceleration),
              visibility(_visibility) {

        elements.insert(titanic);
        elements.insert(iceberg);
    }

    Model::Model() : Model(MODEL_DEFAULT_CLOCK, MODEL_DEFAULT_ACCELERATION, MODEL_DEFAULT_VISIBILITY) {
    }

    Model::~Model() {

        for (auto element : elements) {

            delete element;
        }
    }

    const std::set<PhysicObject2D *> &Model::getElements() const {

        return elements;
    }

    double Model::distance() const {

        return titanic->distance(*iceberg);
    }

    const Titanic *Model::getTitanic() const {

        return titanic;
    }

    Titanic *Model::getTitanic() {
        return titanic;
    }

    Iceberg *Model::getIceberg() {

        return iceberg;
    }

    const Iceberg *Model::getIceberg() const {

        return iceberg;
    }

    bool Model::touching() const {

        return titanic->touch(*iceberg);
    }

    void Model::nextTime(double time) {

        for (auto element : elements) {
            element->nextTime(time);
        }
    }

    void Model::computeFuture(double time) {

        auto nbCycle = static_cast<unsigned int>(time * timeAcceleration / clockStep);

        for (unsigned int i = 0; i < nbCycle; i++) {
            nextTime(clockStep);
        }
    }

    void Model::setTimeAcceleration(double value) {
        timeAcceleration = value;
    }

    double Model::getTimeAcceleration() const {
        return timeAcceleration;
    }

    void Model::resetToDefault() {

        setTimeAcceleration(MODEL_DEFAULT_ACCELERATION);
        setVisibility(MODEL_DEFAULT_VISIBILITY);

        titanic->resetToDefault();
    }

    void Model::reproduceRealScene() {

        setVisibility(MODEL_REAL_VISIBILITY);

        titanic->resetToDefault();
        titanic->reachMachinePower(ENGINE_MAX_POWER);
        titanic->setMachinePower(MODEL_REAL_MACHINE_POWER);
        titanic->setSpeedY(MODEL_REAL_SPEED_Y);
        titanic->setSpeedX(MODEL_REAL_SPEED_X);
        titanic->setPositionX(MODEL_REAL_POSITION_X);
        titanic->setPositionY(MODEL_REAL_POSITION_Y);
        titanic->setOrientation(MODEL_REAL_ORIENTATION);
    }

    void Model::setVisibility(double value) {
        visibility = value;
    }

    double Model::getVisibility() const {
        return visibility;
    }

    void Model::icebergScene() {

        static const double ADD_DISTANCE_Y = 200.0;
        static const double ADD_DISTANCE_X = 15.0;
        static const double ADD_ORIENTATION = 0.002;

        reproduceRealScene();

        setVisibility(INFINITY);

        titanic->setPositionY(titanic->getPositionY() + ADD_DISTANCE_Y);
        titanic->setPositionX(titanic->getPositionX() + ADD_DISTANCE_X);
        titanic->setOrientation(MODEL_REAL_ORIENTATION + ADD_ORIENTATION);
    }
}
