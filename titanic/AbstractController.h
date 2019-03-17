
#ifndef LOGIQUEFLOUE_ABSTRACTCONTROLER_H
#define LOGIQUEFLOUE_ABSTRACTCONTROLER_H


#include "Model.h"
#include "View.h"

class AbstractController {

protected:
    Model &model;
    View &view;

public:
    explicit AbstractController(Model &_model, View &_view);

};


#endif //LOGIQUEFLOUE_ABSTRACTCONTROLER_H
