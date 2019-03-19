#ifndef LOGIQUEFLOUE_MODEL_H
#define LOGIQUEFLOUE_MODEL_H

#include "Titanic.h"
#include "Iceberg.h"

namespace model {

    class Model {

    private:
        std::set<PhysicObject2D *> elements;

    public:
        explicit Model();

        ~Model();
    };
}


#endif //LOGIQUEFLOUE_MODEL_H
