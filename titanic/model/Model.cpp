

#include "Model.h"

namespace model {

    Model::Model() {
        elements.insert(new Titanic());
        elements.insert(new Iceberg());
    }

    Model::~Model() {

        for (auto element : elements) {
            delete element;
        }
    }

    const std::set<PhysicObject2D *> &Model::getElements() const {
        return elements;
    }
}
