#ifndef LOGIQUEFLOUE_VIEW_H
#define LOGIQUEFLOUE_VIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>

#define WINDOWS_TITLE "Save the Titanic"

#define WINDOWS_HEIGHT_SIZE 600
#define WINDOWS_WIDTH_SIZE 1000

class View : public QWidget {

private:
    QBoxLayout *parent;
    QGraphicsScene *titanicViewer;
    QGridLayout *dashboard;

public:
    explicit View();

};


#endif //LOGIQUEFLOUE_VIEW_H
