

#include "Model.h"

namespace model {

    Model::Model() : titanic(new Titanic()), iceberg(new Iceberg()) {
        elements.insert(titanic);
        elements.insert(iceberg);
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
}
