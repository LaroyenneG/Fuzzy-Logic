
#include "fuzzylogic.h"
#include <iostream>
#include <fuzzy/IsBornedTrapezoid.h>
#include "IsTrapezoid.h"
#include "IsTriangle.h"
#include "IsParable.h"
#include "IsBornedTrapezoid.h"
#include "ValueModel.h"
#include "AutomaticPilotController.h"

namespace controller {

    AutomaticPilotController::AutomaticPilotController(Model *_model, View *_view, Draftsman *_draftsman)
            : AbstractController(_model, _view, _draftsman), interpreter(new fuzzylogic::FuzzyInterpreter()) {

        std::ifstream fstream(AUTO_CONTROLLER_INTERPRETER_FILE_PATH);

        interpreter->executeFile(fstream);

        fstream.close();
    }

    void AutomaticPilotController::compute() {

        auto lasers = model->getTitanic()->getLasersSensors().getLasersValues(model->getElements());
        for (auto &laser : lasers) {
            laser *= L_VALUE;
        }

        mutex.lock();

        fuzzylogic::fuzzy::ApproximatelyEqual<double> approximatelyEqual;

        fuzzylogic::fuzzy::AndMin<double> andMin;

        fuzzylogic::fuzzy::NotMinus1<double> aNot;

        fuzzylogic::fuzzy::ThenMin<double> min1;

        fuzzylogic::fuzzy::AggPlus<double> aggPlus;

        fuzzylogic::fuzzy::CogDefuzz<double> cogDefuzz;

        fuzzylogic::FuzzyFactory f(&aNot, &andMin, &approximatelyEqual, &min1, &aggPlus, &cogDefuzz);

        fuzzylogic::ValueModel laser1(lasers[TITANIC_LASER_1_RANK]);
        fuzzylogic::ValueModel laser2(lasers[TITANIC_LASER_2_RANK]);
        fuzzylogic::ValueModel laser3(lasers[TITANIC_LASER_3_RANK]);

        fuzzylogic::ValueModel value(0.0);

        fuzzylogic::IsTriangle laser(1, 1, 0);
        fuzzylogic::IsTrapezoid front(0.95, 1, 0.95, 1);
        fuzzylogic::fuzzy::IsBornedTrapezoid avoidfront(0.25, 0.75, 0.5, 0.6);
        fuzzylogic::IsTriangle left(0, 0.25, 0.5);
        fuzzylogic::IsTrapezoid central(0, 1, 0, 1);
        fuzzylogic::IsTriangle rightTri(0.5, 0.75, 1);
        fuzzylogic::IsTrapezoid rightTra(0.5, 1, 0.5, 1);

        fuzzylogic::Expression *r = f.newAgg(
                f.newThen(f.newIs(&laser, &laser1), f.newIs(&rightTri, &value)),

                f.newAgg(
                        f.newThen(f.newIs(&laser, &laser2), f.newIs(&avoidfront, &value)),
                        f.newAgg(
                                f.newThen(f.newIs(&laser, &laser3), f.newIs(&left, &value)),
                                f.newAgg(
                                        f.newThen(f.newOr(f.newIs(&laser, &laser1), f.newIs(&laser, &laser3)),
                                                  f.newIs(&rightTra, &value)),
                                        f.newThen(
                                                f.newAnd(
                                                        f.newAnd(f.newIs(&front, &laser1), f.newIs(&front, &laser2)),
                                                        f.newIs(&front, &laser3)), f.newIs(&central, &value)
                                        )
                                ))));

        fuzzylogic::Expression *system = f.newMamdaniDefuzz(&value, r,
                                                            0, 1, 0.001);

        double helmValue = system->evaluate();

        std::cout << helmValue << '\n';

        helmValue = helmValue * 2.0 - 1.0;

        view->setHelmValue(helmValue * SLIDER_SIZE_VALUE);

        mutex.unlock();
    }

    AutomaticPilotController::~AutomaticPilotController() {

        delete interpreter;
    }
}