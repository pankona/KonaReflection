#include "ModelManager.h"
#include "BarDirection.h"
#include <cmath>
#include <stdio.h>

// private methods

bool
ModelManager::allBlocksDestroyed() {
    if (blockNum == 0) {
        return true;
    }
    return false;
}

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

    // height edge (top) check
    if (height <= current_position.y + ball->getRadius() / 2) {
        // turn over
        int direction = ball->getDirection();
        int new_direction = (360 - direction) % 360;
        ball->setDirection(new_direction);
    }

    // height edge (bottom) check
    if (0 >= current_position.y - ball->getRadius() / 2) {
        eventNotify(ModelManagerEventListener::ModelManagerEvent::BALL_FALL, NULL);
        return;
    }

    int speed = ball->getSpeed();
    float new_x = cos(rad2deg((float)ball->getDirection())) * (float)speed;
    float new_y = sin(rad2deg((float)ball->getDirection())) * (float)speed;
    Position new_position;
    new_position.x = current_position.x + (int)new_x;
    new_position.y = current_position.y + (int)new_y;

    ball->setPosition(new_position);
}


void
ModelManager::eventNotify(ModelManagerEventListener::ModelManagerEvent in_event, void* arg) {
    for (ModelManagerEventListener* listener : listeners) {
        listener->onModelManagerEvent(in_event, arg);
    }
}

bool
ModelManager::shouldSwingBar(int in_angle) {
    if (in_angle > 90) {
        return true;
    }
    return false;
}

// public method

ModelManager::ModelManager() {
}

void
ModelManager::initialize() {
    field = new Field();
    bar = new Bar();
    ball = new Ball();

    int initialLife = 3;
    player = new Player(initialLife);
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
ModelManager::resetBall() {
    // reset ball position onto bar
    ball->setPosition(bar->getPosition().x, bar->getPosition().y + bar->getHeight() + ball->getRadius());

    // reset ball direction
    ball->setDirection(60);
}

void
ModelManager::setFieldSize(int in_width, int in_height) {
    field->setFieldSize(in_width, in_height);
}

void
ModelManager::initializeBlocks() {
    // ToDo: should refer configuration for blocks initialization.
    int numOfBlocksPerLine = 8;
    int lineNumOfBlocks = 4;
    int blockWidth = field->getWidth() / numOfBlocksPerLine;
    int blockHeight = 30;
    int fieldHeight = field->getHeight();

    for (int j = 0; j < lineNumOfBlocks; j++) {
        for (int i = 0; i < numOfBlocksPerLine; i++) {
            Block* block = new Block();
            block->setSize(blockWidth, blockHeight);
            block->setPosition((i * blockWidth) + (blockWidth / 2),
                               fieldHeight - (blockHeight / 2) - (blockHeight * j));
            block->setLife(1);
            blocks.push_back(block);
        }
    }

    blockNum = blocks.size();
}

int
ModelManager::getBlockNum() {
    return blocks.size();
}

int
ModelManager::getBlockWidth(int index) {
    Block* block = blocks.at(index);
    return block->getWidth();
}

int
ModelManager::getBlockHeight(int index) {
    Block* block = blocks.at(index);
    return block->getHeight();
}

Position
ModelManager::getBlockPosition(int index) {
    Block* block = blocks.at(index);
    return block->getPosition();
}

void
ModelManager::onCollisionBallAndBlock(int in_blockIndex, bool in_needBallTurnOver) {
    Block* block = blocks.at(in_blockIndex);
    Position blockPosition = block->getPosition();
    int blockWidth = block->getWidth();
    int blockHeight = block->getHeight();

    block->decreaseLife(1);
    if (!block->stillAlive()) {
        eventNotify(ModelManagerEventListener::ModelManagerEvent::BLOCK_DIED, &in_blockIndex);
        blockNum--;
    }

    if (allBlocksDestroyed()) {
        eventNotify(ModelManagerEventListener::ModelManagerEvent::ALL_BLOCK_DESTROYED, NULL);
    }

    if (!in_needBallTurnOver) {
        return;
    }

    Position ballPosition = ball->getPosition();
    int ballRadius = ball->getRadius();

    if (ballPosition.x + ballRadius > blockPosition.x - blockWidth / 2 &&
        ballPosition.x - ballRadius < blockPosition.x + blockWidth / 2) {
        // turn over (y)
        int direction = ball->getDirection();
        int new_direction = (360 - direction) % 360;
        ball->setDirection(new_direction);
    } else if (ballPosition.y + ballRadius > blockPosition.y - blockHeight / 2 &&
               ballPosition.y - ballRadius < blockPosition.y + blockHeight) {
        // turn over (x)
        int direction = ball->getDirection();
        int new_direction = (180 - direction) % 360;
        ball->setDirection(new_direction);
    }
}

void
ModelManager::addModelManagerEventListener(ModelManagerEventListener* in_listener) {
    listeners.push_back(in_listener);
}

void
ModelManager::setBallAndBarPositionX(int in_x) {
    lastTouchedPosition.x = in_x;

    if (isTouchOnRightSideOfBar(in_x)) {
        bar->setDirection(BarDirection::RIGHT);
    } else {
        bar->setDirection(BarDirection::LEFT);
    }

    Position p;
    p.x = bar->getPosition().x;
    p.y = ball->getPosition().y;
    ball->setPosition(p);
}

void
ModelManager::setBallSpeed(int in_speed) {
    ball->setSpeed(in_speed);
}

void
ModelManager::decreasePlayerLife() {
    player->decreaseLife();
}

bool
ModelManager::isPlayerStillAlive() {
    return player->isStillAlive();
}

void
ModelManager::startVerticalDraw(int in_y) {
   verticalDrawStart.y = in_y;
   verticalDrawEnd.y = in_y;
}

void
ModelManager::updateVerticalDraw(int in_y) {
   verticalDrawEnd.y = in_y;

   // if draw towards upper, update start position
   // not to stack debt to vetical draw.
   if (verticalDrawEnd.y > verticalDrawStart.y) {
       verticalDrawStart.y = verticalDrawEnd.y;
   }
}

void
ModelManager::endVerticalDraw() {
    int delta = (verticalDrawStart.y - verticalDrawEnd.y) / 2;
    if (shouldSwingBar(delta)) {
        eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING, NULL);
    }

    verticalDrawStart.y = 0;
    verticalDrawEnd.y = 0;
}

int
ModelManager::getVerticalDrawDelta() {
    int delta = verticalDrawStart.y - verticalDrawEnd.y;

    if (delta < 0) {
        return 0;
    } else if (delta > 135) {
        return 135;
    }

    return delta;
}

