#ifndef LOGIQUEFLOUE_MODEL_H
#define LOGIQUEFLOUE_MODEL_H

#define MODEL_DEFAULT_CLOCK 0.001 // s
#define MODEL_DEFAULT_VISIBILITY 2000.0 // m
#define MODEL_REAL_VISIBILITY 500.0 // m
#define MODEL_REAL_MACHINE_POWER 0.0
#define MODEL_DEFAULT_ACCELERATION 1.0
#define MODEL_REAL_SPEED_Y -11.0
#define MODEL_REAL_SPEED_X 0.0
#define MODEL_REAL_POSITION_X 0.0
#define MODEL_REAL_POSITION_Y 634.0
#define MODEL_REAL_ORIENTATION -1.57079632679


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
        double visibility;

    public:
        explicit Model(double _clock, double _timeAcceleration, double _visibility);

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

        void setVisibility(double value);

        double getTimeAcceleration() const;

        ~Model();

        void resetToDefault();

        void reproduceRealScene();

        void icebergScene();

        double getVisibility() const;
    };
}


#endif //LOGIQUEFLOUE_MODEL_H
