
#include "Field.h"
#include "BarDirection.h"

#include <cmath>
#include <stdio.h>

// private mothods

#define rad2deg(a) ((a) / 180.0 * M_PI)

// calculate ball's position at next frame
void
Field::moveBall(float delta) {
    Position current_position = ball->getPosition();

    // check collision to window edge
    // width edge check
    if (width <= current_position.x + ball->getRadius() / 2 || 0 >= current_position.x - ball->getRadius() / 2) {
        // turn over
        int direction = ball->getDirection();
        int new_direction = (180 - direction) % 360;
        ball->setDirection(new_direction);
    }

    // height edge check
    if (height <= current_position.y + ball->getRadius() / 2 || 0 >= current_position.y - ball->getRadius() / 2) {
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
    int center_of_width = this->width / 2;
    printf ("in_x = %d\n", in_x);
    printf ("width = %d, center_of_width = %d\n", this->width, center_of_width);
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

    // notify completion of progress to ViewManager
    notify();
}

void
Field::setFieldSize(int in_width, int in_height) {
    width = in_width;
    height = in_height;
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
        printf ("touch is right side\n");
        bar->setDirection(BarDirection::RIGHT);
    } else {
        printf ("touch is left side\n");
        bar->setDirection(BarDirection::LEFT);
    }
}

void
Field::onTouchMoved(int x, int y) {
    if (isTouchOnRightSide(x)) {
        printf ("touch is moved to right side\n");
        bar->setDirection(BarDirection::RIGHT);
    } else {
        printf ("touch is moved to left side\n");
        bar->setDirection(BarDirection::LEFT);
    }
}

void
Field::onTouchEnded() {
    bar->setDirection(BarDirection::NONE);
}

void
Field::onCollisionBallAndBar() {
    Position ballPosition = ball->getPosition();
    Position barPosition = bar->getPosition();
    int ballRadius = ball->getRadius();
    int barWidth = bar->getWidth();

    if (ballPosition.x + ballRadius / 2 > barPosition.x - barWidth / 2 && 
        ballPosition.x - ballRadius / 2 < barPosition.x + barWidth / 2) {
        int direction = ball->getDirection();
        int new_direction = (360 - direction) % 360;
        ball->setDirection(new_direction);
    } else {
        // if bar and ball has same direction, increase ball speed
        if ((ball->getDirection() >= 0 && ball->getDirection() < 90) ||
            (ball->getDirection() > 270 && ball->getDirection() < 360)) {
            if (bar->getDirection() == BarDirection::RIGHT) {
                // fix me
            } else {
                // turn over
                int direction = ball->getDirection();
                int new_direction = (180 - direction) % 360;
                ball->setDirection(new_direction);
            }
        } else {
            if (bar->getDirection() == BarDirection::LEFT) {
                // fix me
            } else {
                // turn over
                int direction = ball->getDirection();
                int new_direction = (180 - direction) % 360;
                ball->setDirection(new_direction);
            }
        }
    }
}
