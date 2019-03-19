
#include <QtWidgets/QApplication>

#include "View.h"
#include "Model.h"

using namespace view;
using namespace model;

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Model model;

    View view;
    view.show();

    return QApplication::exec();
}
