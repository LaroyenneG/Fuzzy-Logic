
#include <QtWidgets/QApplication>
#include <Draftsman.h>

#include "View.h"

using namespace view;
using namespace model;

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Model model;

    View view;
    view.show();

    Draftsman draftsman(model, view.getScene());
    draftsman.draw();

    return QApplication::exec();
}
