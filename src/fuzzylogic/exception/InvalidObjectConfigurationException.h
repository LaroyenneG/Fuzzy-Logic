#ifndef LOGIQUEFLOUE_INVALIDOBJECTCONFIGURATION_H
#define LOGIQUEFLOUE_INVALIDOBJECTCONFIGURATION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    /*
     * abstract class
     */

    class InvalidObjectConfigurationException : public FuzzyException {

    protected:
        static const std::string MESSAGE;

        InvalidObjectConfigurationException(const std::string &_message, unsigned short _errorCode);
    };
}

#endif //LOGIQUEFLOUE_INVALIDOBJECTCONFIGURATION_H
