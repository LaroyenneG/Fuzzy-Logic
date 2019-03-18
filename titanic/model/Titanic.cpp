
#include "Titanic.h"

namespace model {

    Titanic::Titanic(const std::set<std::pair<double, double >> &points, double _course, double _rudder,
                     double _propellerAccelerator, double _enginePower)
            : Object2D(points),
              course(_course),
              rudder(_rudder),
              propellerSpeed(_propellerAccelerator),
              propellerAccelerator(_enginePower) {

    }
}