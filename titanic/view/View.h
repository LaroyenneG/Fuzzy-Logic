#ifndef LOGIQUEFLOUE_VIEW_H
#define LOGIQUEFLOUE_VIEW_H

#include <QGraphicsView>
#include <QBoxLayout>
#include <QMenuBar>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QProgressBar>
#include <mutex>


#define WINDOWS_TITLE "Save the Titanic"

#define WINDOWS_HEIGHT_SIZE 800
#define WINDOWS_WIDTH_SIZE 1200

#define MS_TO_NDS 1.944
#define RDS_TO_TPM 9.54
/*
namespace controller {
    class CheckBoxController;
}

*/
namespace view {

    class View : public QWidget {

    Q_OBJECT

    public:
        explicit View();

        QGraphicsScene *getScene();

        void setMachinesSpeed(double alt1, double turbine, double alt2);

        void setShipSpeed(double value);

        void setDistance(double value);

        std::mutex &getMutex();

        // void setCheckBoxController(controller::CheckBoxController* checkBoxController) const;

        ~View() override;

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

    public slots:

        void automaticPilotStateChange(bool checked);
    };
}

#endif //LOGIQUEFLOUE_VIEW_H
