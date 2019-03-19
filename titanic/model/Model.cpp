

#include "Model.h"

namespace model {

    Model::Model() {

    }

    Model::~Model() {

        for (auto element : elements) {
            delete element;
        }
    }
}
