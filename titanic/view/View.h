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


#define WINDOWS_TITLE "Save the Titanic"

#define WINDOWS_HEIGHT_SIZE 800
#define WINDOWS_WIDTH_SIZE 1200

#define MS_TO_NDS 1.944
#define RDS_TO_TPM 9.54

#define DEFAULT_VIEW_TIMER_INTERVAL 100

#define DEFAULT_AUTOMATIC_PILOT_INTERVAL 1000

namespace controller {

    class CheckBoxController;

    class TimeWizardController;

    class SliderController;

    class AutomaticPilotController;
}

namespace view {

    class View : public QWidget {

    private:
        std::mutex mutex;

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
        QProgressBar *progressBarLazer1;
        QProgressBar *progressBarLazer2;
        QProgressBar *progressBarLazer3;
        QLabel *distanceLabel;
        QTimer *refreshTimer;
        QTimer *automaticPilotTimer;

    public:
        explicit View();

        QGraphicsScene *getScene();

        void setMachinesSpeed(double alt1, double turbine, double alt2);

        void setShipSpeed(double value);

        void setDistance(double value);

        std::mutex &getMutex();

        void setCheckBoxController(controller::CheckBoxController *checkBoxController) const;

        void setSliderController(controller::SliderController *sliderController) const;

        void setTimeWizardController(controller::TimeWizardController *timeWizardController) const;

        void setAutomaticPilotController(controller::AutomaticPilotController *automaticPilotController) const;

        int getTimeInterval() const;

        void setTimeInterval(int time);

        void display();

        void stopTime();

        void startTime();

        void enableAutomaticPilot();

        void disableAutomaticPilot();

        ~View() override;

        void touching();
    };
}

#endif //LOGIQUEFLOUE_VIEW_H
