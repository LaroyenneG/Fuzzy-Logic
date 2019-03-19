
#include "Draftsman.h"


namespace view {

    const QColor Draftsman::SEA_COLOR(0, 138, 230);

    Draftsman::Draftsman(const model::Model &_model, QGraphicsScene &_scene)
            : model(_model), scene(_scene) {

    }

    void Draftsman::draw() {

        scene.clear();

        scene.setBackgroundBrush(SEA_COLOR);

        for (auto element : model.getElements()) {
            element->drawMe(this);
        }
    }

    void Draftsman::drawElement(const model::PhysicObject2D *object) {

    }
}