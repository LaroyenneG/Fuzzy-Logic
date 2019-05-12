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

#ifdef _ACTIVE_BLACK_BOX_
    std::cout << model->getTitanic()->getBlackBox() << std::endl;
#else
    std::cout << "https://github.com/LaroyenneG/LogiqueFloue.git" << std::endl;
#endif

    delete controlGroup;
    delete model;
    delete view;

    return applicationState;
}
