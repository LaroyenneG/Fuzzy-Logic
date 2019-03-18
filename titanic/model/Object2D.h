#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <map>

namespace model {

    class Object2D {

    private:
        std::set<std::pair<int, int>> points;


    public:
        bool touch(const Object2D &object);
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H