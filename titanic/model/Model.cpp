

#include "Model.h"

namespace model {

    Model::Model() {

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
