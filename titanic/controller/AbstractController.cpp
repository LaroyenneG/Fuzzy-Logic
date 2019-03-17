
#include "AbstractController.h"

namespace controller {

    AbstractController::AbstractController(Model &_model, View &_view)
            : model(_model), view(_view) {

    }
}