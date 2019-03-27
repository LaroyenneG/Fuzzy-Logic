
#include <QApplication>

#include "ControlGroup.h"

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

    delete controlGroup;
    delete model;
    delete view;

    return applicationState;
}
