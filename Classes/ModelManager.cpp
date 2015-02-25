#include "ModelManager.h"
#include "BarDirection.h"
#include <cmath>
#include <stdio.h>

// private methods 

bool
ModelManager::isTouchOnRightSideOfBar(int in_x) {
    int barPositionX = bar->getPosition().x;
    if (in_x > barPositionX) {
        return true;
    }
    return false;
}

void
ModelManager::moveBar(float delta) {
    if (bar->getDirection() == BarDirection::NONE) {
        return;
    }

    if (lastTouchedPosition.x > bar->getPosition().x - bar->getWidth() / 3 &&
        lastTouchedPosition.x < bar->getPosition().x + bar->getWidth() / 3) {
        bar->setDirection(BarDirection::NONE);
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

#define rad2deg(a) ((a) / 180.0 * M_PI)

// calculate ball's position at next frame
void
ModelManager::moveBall(float delta) {
    Position current_position = ball->getPosition();
    int width = field->getWidth();
    int height = field->getHeight();

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

// public method

ModelManager::ModelManager() {
}

void
ModelManager::initialize() {
    field = new Field();
    bar = new Bar();
    ball = new Ball();
}

void
ModelManager::progress(float delta) {
    moveBar(delta);
    moveBall(delta);
}


void
ModelManager::onTouchBegan(int x, int y) {
    lastTouchedPosition.x = x;
    lastTouchedPosition.y = y;

    if (isTouchOnRightSideOfBar(x)) {
        bar->setDirection(BarDirection::RIGHT);
    } else {
        bar->setDirection(BarDirection::LEFT);
    }
}

void
ModelManager::onTouchMoved(int x, int y) {
    lastTouchedPosition.x = x;
    lastTouchedPosition.y = y;

    if (isTouchOnRightSideOfBar(x)) {
        bar->setDirection(BarDirection::RIGHT);
    } else {
        bar->setDirection(BarDirection::LEFT);
    }
}

void
ModelManager::onTouchEnded() {
    bar->setDirection(BarDirection::NONE);
}

void
ModelManager::onCollisionBallAndBar() {
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

void
ModelManager::initializeBar() {
    // init bar position
    bar->setPosition(field->getWidth() / 2, field->getHeight() / 4);
}

Position
ModelManager::getBarPosition() {
    return bar->getPosition();
}

int
ModelManager::getBarWidth() {
    return bar->getWidth();
}

int
ModelManager::getBarHeight() {
    return bar->getHeight();
}

void
ModelManager::initializeBall() {
    // init ball position
    ball->setPosition(field->getWidth() / 2, bar->getPosition().y + bar->getHeight() + ball->getRadius());
}

Position
ModelManager::getBallPosition() {
    return ball->getPosition();
}

int
ModelManager::getBallRadius() {
    return ball->getRadius();
}

void
ModelManager::setFieldSize(int in_width, int in_height) {
    field->setFieldSize(in_width, in_height);
}

void
ModelManager::initializeBlocks() {
    // ToDo: should refer configuration for blocks initialization.
    int numOfBlocksPerLine = 5;
    int blockWidth = field->getWidth() / numOfBlocksPerLine;
    int blockHeight = 30;
    int fieldHeight = field->getHeight();

    for (int i = 0; i < numOfBlocksPerLine; i ++) {
        Block* block = new Block();
        block->setSize(blockWidth, blockHeight);
        block->setPosition((i * blockWidth) + (blockWidth / 2), fieldHeight - (blockHeight / 2));
        blocks.push_back(block);
    }
}

std::vector<Block*>
ModelManager::getBlocks() {
    return blocks;
}

