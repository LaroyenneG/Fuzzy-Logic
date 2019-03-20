#include <sstream>
#include "View.h"

namespace view {

    View::View()
            : parent(nullptr),
              titanicView(nullptr),
              titanicScene(nullptr),
              dashboard(nullptr),
              menuBar(nullptr),
              commandPost(nullptr),
              statisticalBoard(nullptr),
              machineSlider(nullptr),
              rpmMachinesLabel(nullptr),
              speedLabel(nullptr),
              helmSlider(nullptr),
              courseLabel(nullptr),
              automaticPilotCheckBox(nullptr),
              progressBarLazer1(nullptr),
              progressBarLazer2(nullptr),
              progressBarLazer3(nullptr),
              distanceLabel(nullptr) {


        menuBar = new QMenuBar();
        parent = new QBoxLayout(QBoxLayout::TopToBottom);
        titanicScene = new QGraphicsScene();
        titanicView = new QGraphicsView(titanicScene);
        dashboard = new QGridLayout();
        commandPost = new QFormLayout();
        statisticalBoard = new QFormLayout();
        machineSlider = new QSlider(Qt::Horizontal);
        rpmMachinesLabel = new QLabel();
        speedLabel = new QLabel();
        helmSlider = new QSlider(Qt::Horizontal);
        courseLabel = new QLabel();
        automaticPilotCheckBox = new QCheckBox();
        progressBarLazer1 = new QProgressBar();
        progressBarLazer2 = new QProgressBar();
        progressBarLazer3 = new QProgressBar();
        distanceLabel = new QLabel();

        setLayout(parent);

        parent->addWidget(titanicView);
        parent->addLayout(dashboard);
        parent->setMenuBar(menuBar);

        dashboard->addLayout(commandPost, 0, 0);
        dashboard->addLayout(statisticalBoard, 0, 1);

        commandPost->addRow("Machine : ", machineSlider);
        commandPost->addRow("RMP : ", rpmMachinesLabel);
        commandPost->addRow("Speed : ", speedLabel);
        commandPost->addRow("Helm : ", helmSlider);
        commandPost->addRow("Course : ", courseLabel);

        statisticalBoard->addRow("Automatic pilot : ", automaticPilotCheckBox);
        statisticalBoard->addRow("Lazer 1 : ", progressBarLazer1);
        statisticalBoard->addRow("Lazer 2 : ", progressBarLazer2);
        statisticalBoard->addRow("Lazer 3 : ", progressBarLazer3);
        statisticalBoard->addRow("Distance : ", distanceLabel);

        setWindowTitle(WINDOWS_TITLE);
        setFixedSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);

        setMachinesRPM(75, 75, 120);
    }

    View::~View() {

        delete distanceLabel;
        delete progressBarLazer3;
        delete progressBarLazer2;
        delete progressBarLazer1;
        delete automaticPilotCheckBox;
        delete courseLabel;
        delete helmSlider;
        delete speedLabel;
        delete rpmMachinesLabel;
        delete machineSlider;
        delete statisticalBoard;
        delete commandPost;
        delete titanicView;
        delete titanicScene;
        delete dashboard;
        delete parent;
        delete menuBar;
    }

    QGraphicsScene *View::getScene() {
        return titanicScene;
    }

    void View::setMachinesRPM(double alt1, double turbine, double alt2) {

        std::string string =
                "Alt 1 : " +
                std::to_string(static_cast<int>(alt1)) + " | " +
                "Turbine : " +
                std::to_string(static_cast<int>(turbine)) + " | " +
                "Alt 2 : " +
                std::to_string(static_cast<int>(alt2));

        QString qString(string.data());

        rpmMachinesLabel->setText(qString);
    }
}