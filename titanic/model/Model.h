#ifndef LOGIQUEFLOUE_MODEL_H
#define LOGIQUEFLOUE_MODEL_H

#include "Titanic.h"
#include "Iceberg.h"

namespace model {

    class Model {

    private:
        Titanic *titanic;
        Iceberg *iceberg;
        std::set<PhysicObject2D *> elements;

    public:
        explicit Model();

        double distance() const;

        const Titanic *getTitanic() const;

        Titanic *getTitanic();

        Iceberg *getIceberg();

        const Iceberg *getIceberg() const;

        const std::set<PhysicObject2D *> &getElements() const;

        ~Model();
    };
}


#endif //LOGIQUEFLOUE_MODEL_H
