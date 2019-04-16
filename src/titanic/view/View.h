#ifndef LOGIQUEFLOUE_VIEW_H
#define LOGIQUEFLOUE_VIEW_H

#include <QGraphicsView>
#include <QBoxLayout>
#include <QMenuBar>
#include <QFormLayout>
#include <QSlider>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QProgressBar>
#include <mutex>
#include <QFile>


#define WINDOWS_TITLE "Saves the Titanic"

#define WINDOWS_HEIGHT_SIZE 800
#define WINDOWS_WIDTH_SIZE 1200

#define MS_TO_NDS 1.944
#define RDS_TO_TPM 9.54
#define M_TO_MILE 0.000621371


#define DEFAULT_VIEW_TIMER_INTERVAL 100

#define DEFAULT_AUTOMATIC_PILOT_INTERVAL 1000

#define SLIDER_MINIMUM_VALUE -99
#define SLIDER_MAXIMUM_VALUE 99
#define SLIDER_SIZE_VALUE 100

#define COURSE_RDS_TO_DEGREE (180.0/3.1416)

#define STYLE_SHEET_FILE_PATH "../assets/stylesheet.css"


namespace controller {

    class CheckBoxController;

    class TimeWizardController;

    class SliderController;

    class AutomaticPilotController;

    class MenuController;
}

namespace view {

    class View : public QWidget {

    private:
        QBoxLayout *parent;
        QGraphicsView *titanicView;
        QGraphicsScene *titanicScene;
        QGridLayout *dashboard;
        QMenuBar *menuBar;
        QFormLayout *commandPost;
        QFormLayout *statisticalBoard;
        QSlider *machineSlider;
        QLabel *rpmMachinesLabel;
        QLabel *speedLabel;
        QSlider *helmSlider;
        QLabel *courseLabel;
        QCheckBox *automaticPilotCheckBox;
        QProgressBar *progressBarLaser1;
        QProgressBar *progressBarLaser2;
        QProgressBar *progressBarLaser3;
        QLabel *distanceLabel;
        QTimer *refreshTimer;
        QTimer *automaticPilotTimer;

        /* menu items */
        QMenu *simulationMenu;
        QAction *resetAction;
        QAction *pauseAction;
        QAction *playAction;
        QAction *accelerationAction;

        QMenu *sceneMenu;
        QAction *realIcebergSceneAction;
        QAction *icebergSceneAction;

        void createActions();

        void createMenus();

    public:
        explicit View();

        QGraphicsScene *getGraphicsScene();

        QGraphicsView *getGraphicsView();

        void setMachinesSpeed(double alt1, double turbine, double alt2);

        void setLasersValue(double laser1, double laser2, double laser3);

        void setShipSpeed(double value);

        void setDistance(double value);

        void setCheckBoxController(controller::CheckBoxController *checkBoxController) const;

        void setSliderController(controller::SliderController *sliderController) const;

        void setTimeWizardController(controller::TimeWizardController *timeWizardController) const;

        void setAutomaticPilotController(controller::AutomaticPilotController *automaticPilotController) const;

        void setMenuController(controller::MenuController *menuController) const;

        void setHelmValue(double value);

        void setMachinePower(double value);

        void setCourse(double value);

        int getTimeInterval() const;

        void setTimeInterval(int time);

        void display();

        void stopTime();

        void startTime();

        void enableAutomaticPilot();

        void disableAutomaticPilot();

        void touching();

        bool automaticPilotIsEnable();

        void lockDashboard();

        void unlockDashboard();

        ~View() override;
    };
}

#endif //LOGIQUEFLOUE_VIEW_H
