#ifndef LOGIQUEFLOUE_VIEW_H
#define LOGIQUEFLOUE_VIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QMenuBar>


#define WINDOWS_TITLE "Save the Titanic"

#define WINDOWS_HEIGHT_SIZE 800
#define WINDOWS_WIDTH_SIZE 1200

class View : public QWidget {

private:
    QBoxLayout *parent;
    QGraphicsView *titanicView;
    QGraphicsScene *titanicScene;
    QGridLayout *dashboard;
    QMenuBar *menuBar;

public:
    explicit View();

    ~View() override;
};

#endif //LOGIQUEFLOUE_VIEW_H
