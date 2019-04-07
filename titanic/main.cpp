#include <QApplication>
#include "ControlGroup.h"

#define _BLACK_BOX

using namespace view;
using namespace model;
using namespace controller;

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    auto *model = new Model();
    auto *view = new View();
    auto *controlGroup = new ControlGroup(model, view);

    view->display();

    int applicationState = QApplication::exec();

#ifdef _BLACK_BOX
    std::cout << model->getTitanic()->getBlackBox() << std::endl;
#endif

    delete controlGroup;
    delete model;
    delete view;

    return applicationState;
}
