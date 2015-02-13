
#include "GameControl.h"

void
GameControl::update(float delta) {
    field.progress(delta);
    dball->updatePosition();
}

void
GameControl::addDBall(DrawableBall* in_dball) {
    dball = in_dball;
    field.addBall(in_dball->getBall());
}
