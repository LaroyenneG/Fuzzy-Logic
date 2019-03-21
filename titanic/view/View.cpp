#include <sstream>
#include <iostream>

#include "CheckBoxController.h"
#include "SliderController.h"
#include "TimeWizardController.h"
#include "AutomaticPilotController.h"


#define COLLISIONS_TITLE "Titanic sank"
#define COLLISIONS_MESSAGE "The ship touching the iceberg :-("

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
              distanceLabel(nullptr),
              refreshTimer(nullptr),
              automaticPilotTimer(nullptr) {


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
        refreshTimer = new QTimer(this);
        automaticPilotTimer = new QTimer(this);

        automaticPilotTimer->setInterval(DEFAULT_AUTOMATIC_PILOT_INTERVAL);
        refreshTimer->setInterval(DEFAULT_VIEW_TIMER_INTERVAL);

        machineSlider->setRange(SLIDER_MINIMUM_VALUE, SLIDER_MAXIMUM_VALUE);
        helmSlider->setRange(SLIDER_MINIMUM_VALUE, SLIDER_MAXIMUM_VALUE);

        setLayout(parent);

        parent->addWidget(titanicView);
        parent->addLayout(dashboard);
        parent->setMenuBar(menuBar);

        dashboard->addLayout(commandPost, 0, 0);
        dashboard->addLayout(statisticalBoard, 0, 1);

        commandPost->addRow("Machine (%) : ", machineSlider);
        commandPost->addRow("Rotation (rpm) : ", rpmMachinesLabel);
        commandPost->addRow("Speed (nd) : ", speedLabel);
        commandPost->addRow("Helm (%) : ", helmSlider);
        commandPost->addRow("Course (°) : ", courseLabel);

        statisticalBoard->addRow("Automatic pilot : ", automaticPilotCheckBox);
        statisticalBoard->addRow("Lazer 1 (%) : ", progressBarLazer1);
        statisticalBoard->addRow("Lazer 2 (%) : ", progressBarLazer2);
        statisticalBoard->addRow("Lazer 3 (%) : ", progressBarLazer3);
        statisticalBoard->addRow("Distance (m) : ", distanceLabel);

        setWindowTitle(WINDOWS_TITLE);
        // setFixedSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);
    }

    View::~View() {

        delete refreshTimer;
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

    void View::setMachinesSpeed(double alt1, double turbine, double alt2) {

        std::string string =
                "Alt 1 : " +
                std::to_string(static_cast<int>(alt1 * RDS_TO_TPM)) + " | " +
                "Turbine : " +
                std::to_string(static_cast<int>(turbine * RDS_TO_TPM)) + " | " +
                "Alt 2 : " +
                std::to_string(static_cast<int>(alt2 * RDS_TO_TPM));

        QString qString(string.data());

        rpmMachinesLabel->setText(qString);
    }

    std::mutex &View::getMutex() {
        return mutex;
    }

    void View::setShipSpeed(double value) {

        int nds = static_cast<int>(value * MS_TO_NDS);

        std::string string = std::to_string(nds);

        QString qString(string.data());

        speedLabel->setText(qString);
    }

    void View::setDistance(double value) {

        int nd = static_cast<int>(value);

        std::string string = std::to_string(nd);

        QString qString(string.data());

        distanceLabel->setText(qString);
    }

    void View::setCheckBoxController(controller::CheckBoxController *checkBoxController) const {

        QObject::connect(automaticPilotCheckBox, SIGNAL(clicked(bool)), checkBoxController,
                         SLOT(automaticPilotStateChange(bool)));
    }

    void View::setSliderController(controller::SliderController *sliderController) const {

        QObject::connect(machineSlider, SIGNAL(valueChanged(int)), sliderController,
                         SLOT(machinePowerSliderValueChanged(int)));

        QObject::connect(helmSlider, SIGNAL(valueChanged(int)), sliderController, SLOT(helmSliderValueChanged(int)));
    }

    void View::setTimeWizardController(controller::TimeWizardController *timeWizardController) const {

        QObject::connect(refreshTimer, SIGNAL(timeout()), timeWizardController, SLOT(nextTime()));
    }

    void View::setAutomaticPilotController(controller::AutomaticPilotController *automaticPilotController) const {

        QObject::connect(automaticPilotTimer, SIGNAL(timeout()), automaticPilotController, SLOT(compute()));
    }

    int View::getTimeInterval() const {
        return refreshTimer->interval();
    }

    void View::setTimeInterval(int time) {
        refreshTimer->setInterval(time);
    }

    void View::display() {
        startTime();
        show();
    }

    void View::stopTime() {
        refreshTimer->stop();
    }

    void View::startTime() {

        if (refreshTimer->isActive()) {
            refreshTimer->stop();
        }

        refreshTimer->start();
    }

    void View::touching() {
        QMessageBox::information(this, QString(COLLISIONS_TITLE), QString(COLLISIONS_MESSAGE));
    }

    void View::enableAutomaticPilot() {

        if (automaticPilotTimer->isActive()) {
            automaticPilotTimer->stop();
        }

        automaticPilotTimer->start();
    }

    void View::disableAutomaticPilot() {
        automaticPilotTimer->stop();
    }

    void View::setHelmValue(double value) {

        helmSlider->setValue(static_cast<int>(value));
    }

    void View::setMachinePower(double value) {

        machineSlider->setValue(static_cast<int>(value * (SLIDER_MAXIMUM_VALUE - SLIDER_MINIMUM_VALUE)));
    }
}