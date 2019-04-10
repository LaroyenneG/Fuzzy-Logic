
#include "PointAlreadyAddedShapeException.h"


namespace fuzzylogic::exception {

    const std::string PointAlreadyAddedShapeException::MESSAGE("The required operator has been null");

    const unsigned short PointAlreadyAddedShapeException::ERROR_CODE = 5;

    PointAlreadyAddedShapeException::PointAlreadyAddedShapeException() : FuzzyException(MESSAGE, ERROR_CODE) {

    }
}