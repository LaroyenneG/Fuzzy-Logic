
#include <QtWidgets/QApplication>

#include "View.h"

using namespace view;

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    View view;
    view.show();

    return QApplication::exec();
}
