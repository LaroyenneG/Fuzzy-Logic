#ifndef FUZZY_LOGIC_COREOBJECT_H
#define FUZZY_LOGIC_COREOBJECT_H

namespace fuzzylogic::core {

    template<typename T>
    class CoreObject {

    public:
        CoreObject() = default;

        virtual ~CoreObject() = default;
    };
}

#endif //FUZZY_LOGIC_COREOBJECT_H
