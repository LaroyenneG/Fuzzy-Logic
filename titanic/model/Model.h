#ifndef LOGIQUEFLOUE_MODEL_H
#define LOGIQUEFLOUE_MODEL_H

#define MODEL_DEFAULT_CLOCK 0.001 // s
#define MODEL_DEFAULT_ACCELERATION 1.0 // %

#include "Titanic.h"
#include "Iceberg.h"

namespace model {

    class Model {

    private:
        Titanic *titanic;
        Iceberg *iceberg;
        std::set<PhysicObject2D *> elements;

        const double clockStep;

        double timeAcceleration;

    public:
        explicit Model(double _clock, double _timeAcceleration);

        explicit Model();

        double distance() const;

        const Titanic *getTitanic() const;

        Titanic *getTitanic();

        Iceberg *getIceberg();

        const Iceberg *getIceberg() const;

        const std::set<PhysicObject2D *> &getElements() const;

        bool touching() const;

        void nextTime(double time);

        void computeFuture(double time);

        void setTimeAcceleration(double value);

        double getTimeAcceleration() const;

        ~Model();
    };
}


#endif //LOGIQUEFLOUE_MODEL_H
