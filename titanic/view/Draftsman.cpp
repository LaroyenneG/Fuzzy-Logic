
#include "Draftsman.h"


namespace view {

    const QColor Draftsman::SEA_COLOR(0, 138, 230);

    Draftsman::Draftsman(const Model &_model, QGraphicsScene &_qGraphicsScene)
            : model(_model), qGraphicsScene(_qGraphicsScene) {

    }

    void Draftsman::draw() {
        qGraphicsScene.clear();
        qGraphicsScene.setBackgroundBrush(SEA_COLOR);
    }
}