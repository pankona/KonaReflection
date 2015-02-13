
#include "Field.h"

void
Field::addDBall(DrawableBall* in_dball) {
    this->dBall = in_dball;
}

DrawableBall *
Field::getDBall() {
    return this->dBall;
}

void
Field::moveDBall(float delta) {
    this->dBall->update(delta);
}

void
Field::progress(float delta) {
    moveDBall(delta);
}

