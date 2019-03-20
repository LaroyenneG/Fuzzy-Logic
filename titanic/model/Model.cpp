

#include "Model.h"

namespace model {

    Model::Model() : titanic(new Titanic()), iceberg(new Iceberg(100, 200)) {
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
        return 0;
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
}
