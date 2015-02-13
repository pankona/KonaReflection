
#include "Field.h"

void
Field::addBall(Ball* in_ball) {
    this->ball = in_ball;
}

Ball*
Field::getBall() {
    return this->ball;
}

void
Field::moveBall(float delta) {
    // calculate ball's position at next frame
    Position current_position = ball->getPosition();
    Position new_position;
    new_position.x = current_position.x + ball->getSpeed();
    new_position.y = current_position.y + ball->getSpeed();
    ball->setPosition(new_position);
}

void
Field::progress(float delta) {
    moveBall(delta);
}

