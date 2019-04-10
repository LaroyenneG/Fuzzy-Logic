#ifndef LOGIQUEFLOUE_TARGETNULLEXCEPTION_H
#define LOGIQUEFLOUE_TARGETNULLEXCEPTION_H

#include "InvalidObjectConfigurationException.h"

namespace fuzzylogic::exception {

    class TargetNullException : public InvalidObjectConfigurationException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit TargetNullException();
    };
}

#endif //LOGIQUEFLOUE_TARGETNULLEXCEPTION_H
