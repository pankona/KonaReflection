
#include "Field.h"
#include "BarDirection.h"

#include <cmath>
#include <stdio.h>

// private mothods

#define rad2deg(a) ((a) / 180.0 * M_PI)

void
Field::moveBall(float delta) {
    // calculate ball's position at next frame
    Position current_position = ball->getPosition();

    // check collision to window edge
    // width edge check
    if (width <= current_position.x + ball->getRadius() || 0 >= current_position.x) {
        // turn over
        int direction = ball->getDirection();
        int new_direction = (180 - direction) % 360;
        ball->setDirection(new_direction);
    }

    // height edge check
    if (height <= current_position.y + ball->getRadius() || 0 >= current_position.y) {
        // turn over
        int direction = ball->getDirection();
        int new_direction = (360 - direction) % 360;
        ball->setDirection(new_direction);
    }

    int speed = ball->getSpeed();
    float new_x = cos(rad2deg((float)ball->getDirection())) * (float)speed;
    float new_y = sin(rad2deg((float)ball->getDirection())) * (float)speed;
    Position new_position;
    new_position.x = current_position.x + (int)new_x;
    new_position.y = current_position.y + (int)new_y;

    ball->setPosition(new_position);
}

bool
Field::isTouchOnRightSide(int in_x) {
    int center_of_width = width / 2;
    if (in_x > center_of_width) {
        return true;
    }
    return false;
}

void
Field::moveBar(float delta) {
    if (bar->getDirection() == BarDirection::NONE) {
        return;
    }

    Position currentPosition = bar->getPosition();
    Position newPosition;
    if (bar->getDirection() == BarDirection::RIGHT) {
        newPosition.x = currentPosition.x + bar->getSpeed();
    } else if (bar->getDirection() == BarDirection::LEFT) {
        newPosition.x = currentPosition.x - bar->getSpeed();
    } else {
        // should never reach
        newPosition.x = currentPosition.x;
    }
    newPosition.y = currentPosition.y;
    bar->setPosition(newPosition);
}

// public methods

Field::Field() {
}

void
Field::addBall(Ball* in_ball) {
    ball = in_ball;
}

Ball*
Field::getBall() {
    return ball;
}

void
Field::setBar(Bar *in_bar) {
    bar = in_bar;
}

Bar*
Field::getBar() {
    return bar;
}

void
Field::progress(float delta) {
    moveBall(delta);
    moveBar(delta);
}

void
Field::setFieldSize(int in_width, int in_height) {
    this->width = in_width;
    this->height = in_height;
}

int
Field::getWidth() {
    return width;
}

int
Field::getHeight() {
    return height;
}

void
Field::onTouchBegan(int x, int y) {
    if (isTouchOnRightSide(x)) {
        bar->setDirection(BarDirection::RIGHT);
    } else {
        bar->setDirection(BarDirection::LEFT);
    }
}

void
Field::onTouchEnded() {
    bar->setDirection(BarDirection::NONE);
}
