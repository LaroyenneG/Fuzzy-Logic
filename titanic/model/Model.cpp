

#include "Model.h"

namespace model {

    Model::Model(double _clock, double _timeAcceleration)
            : titanic(new Titanic()), iceberg(new Iceberg()), clockStep(_clock), timeAcceleration(_timeAcceleration) {
        elements.insert(titanic);
        // elements.insert(iceberg);
    }

    Model::Model() : Model(MODEL_DEFAULT_CLOCK, MODEL_DEFAULT_ACCELERATION) {
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

        return false;
        titanic->touch(*iceberg);
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
}
