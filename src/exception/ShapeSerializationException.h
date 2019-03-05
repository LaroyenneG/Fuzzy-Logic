#ifndef LOGIQUEFLOUE_SHAPESERIALIZATIONEXCEPTION_H
#define LOGIQUEFLOUE_SHAPESERIALIZATIONEXCEPTION_H

#include "FuzzyException.h"

namespace exception {

    class ShapeSerializationException : public FuzzyException {

    private:
        static const std::string MESSAGE;

        static const unsigned short ERROR_CODE;

    public:
        explicit ShapeSerializationException();
    };
}

#endif //LOGIQUEFLOUE_SHAPESERIALIZATIONEXCEPTION_H
