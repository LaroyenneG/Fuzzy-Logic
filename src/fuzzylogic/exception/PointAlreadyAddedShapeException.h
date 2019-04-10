#ifndef LOGIQUEFLOUE_POINTALREADYADDEDSHAPEEXCEPTION_H
#define LOGIQUEFLOUE_POINTALREADYADDEDSHAPEEXCEPTION_H

#include "FuzzyException.h"

namespace fuzzylogic::exception {

    class PointAlreadyAddedShapeException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit PointAlreadyAddedShapeException();
    };
}


#endif //LOGIQUEFLOUE_POINTALREADYADDEDSHAPEEXCEPTION_H
