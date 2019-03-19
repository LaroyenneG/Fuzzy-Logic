#include "View.h"

namespace view {

    View::View()
            : parent(nullptr),
              titanicView(nullptr),
              titanicScene(nullptr),
              dashboard(nullptr),
              menuBar(nullptr) {

        menuBar = new QMenuBar();
        parent = new QBoxLayout(QBoxLayout::TopToBottom);
        titanicScene = new QGraphicsScene();
        titanicView = new QGraphicsView(titanicScene);
        dashboard = new QGridLayout();

        setLayout(parent);

        parent->addWidget(titanicView);
        parent->addLayout(dashboard);
        parent->setMenuBar(menuBar);


        setWindowTitle(WINDOWS_TITLE);
        setFixedSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);
    }

    View::~View() {

        delete titanicView;
        delete titanicScene;
        delete dashboard;
        delete parent;
        delete menuBar;
    }

    QGraphicsScene &View::getScene() {
        return *titanicScene;
    }
}