#include "ShapeSerializationException.h"

namespace exception {

    const std::string ShapeSerializationException::MESSAGE("Shape serialization format was incorrect");

    const unsigned short ShapeSerializationException::ERROR_CODE = 7;

    ShapeSerializationException::ShapeSerializationException() : FuzzyException(MESSAGE, ERROR_CODE) {
    }
}