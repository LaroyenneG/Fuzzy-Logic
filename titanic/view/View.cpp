#include <sstream>
#include <iostream>

#include "CheckBoxController.h"
#include "SliderController.h"
#include "TimeWizardController.h"
#include "AutomaticPilotController.h"
#include "MenuController.h"
#include "View.h"


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
              progressBarLaser1(nullptr),
              progressBarLaser2(nullptr),
              progressBarLaser3(nullptr),
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
        progressBarLaser1 = new QProgressBar();
        progressBarLaser2 = new QProgressBar();
        progressBarLaser3 = new QProgressBar();
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
        commandPost->addRow("Course (degree) : ", courseLabel);

        statisticalBoard->addRow("Automatic pilot : ", automaticPilotCheckBox);
        statisticalBoard->addRow("Laser 1 (%) : ", progressBarLaser1);
        statisticalBoard->addRow("Laser 2 (%) : ", progressBarLaser2);
        statisticalBoard->addRow("Laser 3 (%) : ", progressBarLaser3);
        statisticalBoard->addRow("Distance (m) : ", distanceLabel);


        QFile styleSheetFile(STYLE_SHEET_FILE_PATH);
        styleSheetFile.open(QFile::ReadOnly);
        setStyleSheet(QLatin1String(styleSheetFile.readAll()));
        styleSheetFile.close();

        setWindowTitle(WINDOWS_TITLE);
        setMinimumSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);
    }

    View::~View() {

        delete refreshTimer;
        delete distanceLabel;
        delete progressBarLaser3;
        delete progressBarLaser2;
        delete progressBarLaser1;
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

    QGraphicsScene *View::getGraphicsScene() {
        return titanicScene;
    }

    void View::setMachinesSpeed(double alt1, double turbine, double alt2) {

        std::string string =
                "Alternative left : " +
                std::to_string(static_cast<int>(alt1 * RDS_TO_TPM)) + " | " +
                "Turbine : " +
                std::to_string(static_cast<int>(turbine * RDS_TO_TPM)) + " | " +
                "Alternative right : " +
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

    void View::setMenuController(controller::MenuController *menuController) const {

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

    void View::setCourse(double value) {

        int course = static_cast<int>(value * COURSE_RDS_TO_DEGREE);

        std::string string = std::to_string(course);

        QString qString(string.data());

        courseLabel->setText(qString);
    }

    QGraphicsView *View::getGraphicsView() {

        return titanicView;
    }

    void View::setLasersValue(double l1, double l2, double l3) {

        progressBarLaser1->setValue(static_cast<int>(l1 * 100.0));
        progressBarLaser2->setValue(static_cast<int>(l2 * 100.0));
        progressBarLaser3->setValue(static_cast<int>(l3 * 100.0));
    }
}