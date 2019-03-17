#include "View.h"


View::View()
        : parent(new QBoxLayout(QBoxLayout::TopToBottom, this)),
          titanicViewer(new QGraphicsScene(parent)) {

    setWindowTitle(WINDOWS_TITLE);
    setFixedSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);
}
