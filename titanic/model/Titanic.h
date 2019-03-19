
#ifndef LOGIQUEFLOUE_TITANIC_H
#define LOGIQUEFLOUE_TITANIC_H

#include <vector>

#include "Object2D.h"
#include "Engine.h"
#include "Rudder.h"

#define DEFAULT_COURSE 0.0
#define DEFAULT_RUDDER 0.0
#define TITANIC_DEFAULT_WEIGHT 52310000.0

#define ENGINES_COUNTER 3

namespace model {

    class Titanic : public Object2D {

    private:
        const static std::set<std::pair<double, double >> DEFAULT_POINTS;

        double course;  // radian

        Rudder rudder;

        const std::array<Engine *, ENGINES_COUNTER> engines;

    public:
        explicit Titanic(const std::set<std::pair<double, double >> &points, double _course, double _weight);

        explicit Titanic();

        ~Titanic() override;
    };
}

#endif //LOGIQUEFLOUE_TITANIC_H
