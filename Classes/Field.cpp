
#include "Field.h"

#include <cmath>
#include <stdio.h>

void
Field::addBall(Ball* in_ball) {
    this->ball = in_ball;
}

Ball*
Field::getBall() {
    return this->ball;
}

#define M_PI (3.141592)
#define rad2deg(a) ((a) / 180.0 * M_PI)

void
Field::moveBall(float delta) {
    // calculate ball's position at next frame
    Position current_position = ball->getPosition();

    // check collision to window edge
    // width edge check
    if (500 <= current_position.x || 0 >= current_position.x) {
        // turn over
        printf ("turn over x. cpx = %d, cpy = %d\n", current_position.x, current_position.y);
        int direction = ball->getDirection();
        int new_direction = (180 - direction) % 360;
        ball->setDirection(new_direction);
    }

    // height edge check
    if (500 <= current_position.y || 0 >= current_position.y) {
        // turn over
        printf ("turn over y. cpx = %d, cpy = %d\n", current_position.x, current_position.y);
        int direction = ball->getDirection();
        int new_direction = (360 - direction) % 360;
        ball->setDirection(new_direction);
    }

    printf ("current direction = %d\n", ball->getDirection());
    int speed = ball->getSpeed();
    float new_x = cos(rad2deg((float)ball->getDirection())) * (float)speed;
    float new_y = sin(rad2deg((float)ball->getDirection())) * (float)speed;
    Position new_position;
    new_position.x = current_position.x + (int)new_x;
    new_position.y = current_position.y + (int)new_y;

    ball->setPosition(new_position);
}

void
Field::progress(float delta) {
    moveBall(delta);
}

void
Field::setFieldSize(int in_width, int in_height) {
    this->width = in_width;
    this->height = in_height;
}
