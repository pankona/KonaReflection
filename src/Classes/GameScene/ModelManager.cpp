#include "ModelManager.h"
#include "BarDirection.h"
#include "KonaVector2D.h"
#include "KonaCircle.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <float.h>
#include <unistd.h>

//#define TEST

// private methods

#define BALL_REFLECT_X() \
            ball->addVector(Kona::Vector(Kona::Point(-1 * ball->getSpeedX() * 2, 0)))

#define BALL_REFLECT_Y() \
            ball->addVector(Kona::Vector(Kona::Point(0, -1 * ball->getSpeedY() * 2)))

const int
ModelManager::swingBarAngleTable[] = {
      -45, 45, 135, 0
};

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

    if (bar->isSwinging()) {
        progressBarSwinging();
    }

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
        if (bar->getAngle() > -10) {
            bar->setAngle(bar->getAngle() - 1);
        }
    } else if (bar->getDirection() == BarDirection::LEFT) {
        newPosition.x = currentPosition.x - bar->getSpeed();
        if (bar->getAngle() < 10) {
            bar->setAngle(bar->getAngle() + 1);
        }
    } else {
        newPosition.x = currentPosition.x;
    }
    newPosition.y = currentPosition.y;
    bar->setPosition(newPosition);
}

enum EIGHT_DIRECTION {
    E_RIGHT,
    E_LEFT,
    E_UP,
    E_DOWN,
    E_RIGHT_UP,
    E_RIGHT_DOWN,
    E_LEFT_UP,
    E_LEFT_DOWN,
    E_UNKNOWN
};

static Block::SIDE
calcWhichCornerByCircle(Block in_block, Kona::Circle in_circle) {

    Kona::Vector2D blockUpperLine = in_block.getVector2DOfBlockSide(Block::SIDE::UPPER);
    Kona::Vector2D blockBottomLine = in_block.getVector2DOfBlockSide(Block::SIDE::DOWNER);

    if (blockUpperLine.getStartPosition() == in_circle.getPosition()) {
        return Block::SIDE::CORNER_LEFTER_UPPER;
    } else if (blockUpperLine.getTerminalPosition() == in_circle.getPosition()) {
        return Block::SIDE::CORNER_RIGHTER_UPPER;
    } else if (blockBottomLine.getStartPosition() == in_circle.getPosition()) {
        return Block::SIDE::CORNER_LEFTER_DOWNER;
    } else if (blockBottomLine.getTerminalPosition() == in_circle.getPosition()) {
        return Block::SIDE::CORNER_RIGHTER_DOWNER;
    }

    return Block::SIDE::UNKNOWN;
}

static bool
doCollideVector2DAndBlockCorner(Ball* in_ball, Block* in_block, Block::SIDE in_blockSideToCheck,
                                Kona::Vector2D* out_distance, Block::SIDE* out_whichCorner) {
    Kona::Circle circle1;
    Kona::Circle circle2;

    float radius = in_ball->getRadius();
    Kona::Vector2D moveLine = in_ball->getVector2D();

    Kona::Vector2D blockSide = in_block->getVector2DOfBlockSide(in_blockSideToCheck);
    circle1 = Kona::Circle(blockSide.getStartPosition(), radius);
    circle2 = Kona::Circle(blockSide.getTerminalPosition(), radius);
    
    Kona::Point intersectPoint1;
    Kona::Point intersectPoint2;

    Kona::Point intersectPointA;
    int intersectPointNumA = circle1.intersectsVector2D(moveLine, &intersectPoint1, &intersectPoint2);
    if (intersectPointNumA == 1) {
        intersectPointA = intersectPoint1;
    } else if (intersectPointNumA == 2) {
        if (moveLine.distanceToPoint(intersectPoint1) < moveLine.distanceToPoint(intersectPoint2)) {
            intersectPointA = intersectPoint1;
        } else {
            intersectPointA = intersectPoint2;
        }
    }

    Kona::Point intersectPointB;
    int intersectPointNumB = circle2.intersectsVector2D(moveLine, &intersectPoint1, &intersectPoint2);
    if (intersectPointNumB == 1) {
        intersectPointB = intersectPoint1;
    } else if (intersectPointNumB == 2) {
        if (moveLine.distanceToPoint(intersectPoint1) < moveLine.distanceToPoint(intersectPoint2)) {
            intersectPointB = intersectPoint1;
        } else {
            intersectPointB = intersectPoint2;
        }
    }

    Kona::Point intersectPoint;
    if (intersectPointNumA != 0 && intersectPointNumB != 0) {
        if (moveLine.distanceToPoint(intersectPointA) < moveLine.distanceToPoint(intersectPointB)) {
            intersectPoint = intersectPointA;
            *out_whichCorner = calcWhichCornerByCircle(*in_block, circle1);
        } else {
            intersectPoint = intersectPointB;
            *out_whichCorner = calcWhichCornerByCircle(*in_block, circle2);
        }
    } else if (intersectPointNumA != 0) {
        intersectPoint = intersectPointA;
        *out_whichCorner = calcWhichCornerByCircle(*in_block, circle1);
    } else if (intersectPointNumB != 0) {
        intersectPoint = intersectPointB;
        *out_whichCorner = calcWhichCornerByCircle(*in_block, circle2);
    } else {
        return false;
    }

    *out_distance = Kona::Vector2D(moveLine.getStartPosition(), intersectPoint);
    return true;
}

static bool
doCollideVector2DAndBlock(Ball* in_ball, Block* in_block, Block::SIDE in_blockSideToCheck,
                          Kona::Vector2D* out_distance) {
    Kona::Vector2D in_v2d = in_ball->getVector2D();
    int ballRadius = in_ball->getRadius();
    Kona::Vector2D blockSide = in_block->getVector2DOfBlockSide(in_blockSideToCheck);
    
    Kona::Point startPosition = blockSide.getStartPosition();
    switch (in_blockSideToCheck) {
        case Block::UPPER:
            blockSide.setStartPosition(Kona::Point(startPosition.x,
                                                   startPosition.y + ballRadius));
            break;
        case Block::DOWNER:
            blockSide.setStartPosition(Kona::Point(startPosition.x,
                                                   startPosition.y - ballRadius));
            break;
        case Block::RIGHTER:
            blockSide.setStartPosition(Kona::Point(startPosition.x + ballRadius,
                                                   startPosition.y));
            break;
        case Block::LEFTER:
            blockSide.setStartPosition(Kona::Point(startPosition.x - ballRadius,
                                                   startPosition.y));
            break;
        case Block::UNKNOWN:
        default:
            return false;
    }

    Kona::Point intersectPoint;
    if (blockSide.calcIntersectPoint(in_v2d, &intersectPoint)) {
        *out_distance = Kona::Vector2D(in_v2d.getStartPosition(), intersectPoint);
        return true;
    }
    return false;
}

static float
calcReflectAngleByCollideCorner(float in_currentBallAngle, Block::SIDE in_blockCorner) {
    int unitLength = 1;
    Kona::Vector v(unitLength, in_currentBallAngle);

    switch (in_blockCorner) {
        case Block::SIDE::CORNER_LEFTER_DOWNER:
            v += Kona::Vector(std::sqrt(2), 180 + 45);
            break;
        case Block::SIDE::CORNER_LEFTER_UPPER:
            v += Kona::Vector(std::sqrt(2), 90 + 45);
            break;
        case Block::SIDE::CORNER_RIGHTER_DOWNER:
            v += Kona::Vector(std::sqrt(2), 270 + 45);
            break;
        case Block::SIDE::CORNER_RIGHTER_UPPER:
            v += Kona::Vector(std::sqrt(2), 0 + 45);
            break;
        default:
            std::cout << "[" << __func__ << "][" << __LINE__ << "] should never reach here!" << std::endl;
            return 0;
    }

    return v.getAngle();
}

static bool
isBallNearWhileBarSwinging(Bar in_bar, Ball in_ball) {
    if (!in_bar.isSwinging()) {
        return false;
    }

    Position barPosition = in_bar.getPosition();
    Position ballPosition = in_ball.getPosition();

    float delta_x = std::abs(barPosition.x - ballPosition.x);
    float delta_y = std::abs(barPosition.y - ballPosition.y);

    float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance < in_bar.getWidth() + in_ball.getRadius()) {
        return true;
    }

    return false;
}
#define rad2deg(a) ((a) / 180.0 * M_PI)

// calculate ball's position at next frame
void
ModelManager::moveBall(float delta) {
    int width = field->getWidth();
    int height = field->getHeight();
    int radius = ball->getRadius();

    // temp ball initialization
    Ball tempBall;
    tempBall.setPosition(ball->getPosition().x, ball->getPosition().y);
    tempBall.setVector(ball->getVector());

    while (true) {
        Position current_position = tempBall.getPosition();

        EIGHT_DIRECTION ballDir = E_UNKNOWN;

        if (ball->isTowardUp()) {
            if (ball->isTowardRight()) {
                ballDir = E_RIGHT_UP;
            } else if (ball->isTowardLeft()) {
                ballDir = E_LEFT_UP;
            } else {
                ballDir = E_UP;
            }
        } else if (ball->isTowardDown()) {
            if (ball->isTowardRight()) {
                ballDir = E_RIGHT_DOWN;
            } else if (ball->isTowardLeft()) {
                ballDir = E_LEFT_DOWN;
            } else {
                ballDir = E_DOWN;
            }
        } else if (ball->isTowardRight()) {
            ballDir = E_RIGHT;
        } else if (ball->isTowardLeft()) {
            ballDir = E_LEFT;
        } else {
            ballDir = E_UNKNOWN;
        }

        Kona::Vector2D distance;
        Kona::Vector2D minDistance;
        Block::SIDE blockSideToCheck = Block::SIDE::UNKNOWN;
        Block::SIDE blockSideActuallyUse = Block::SIDE::UNKNOWN;;
        Block::SIDE whichCorner = Block::SIDE::UNKNOWN;
        float minLength = FLT_MAX;
        int blockIndex = -1;

        for (int i = 0; i < blocks.size(); i++) {
            if (!blocks.at(i)->stillAlive()) {
                continue;
            }

            if (ballDir == E_RIGHT    ||
                ballDir == E_RIGHT_UP ||
                ballDir == E_RIGHT_DOWN) {
                blockSideToCheck = Block::SIDE::LEFTER;
            } else if (ballDir == E_LEFT    ||
                       ballDir == E_LEFT_UP ||
                       ballDir == E_LEFT_DOWN) {
                blockSideToCheck = Block::SIDE::RIGHTER;
            }

            if (blockSideToCheck != Block::SIDE::UNKNOWN) {
                if (doCollideVector2DAndBlock(ball, blocks.at(i), blockSideToCheck, &distance)) {
                    if (distance.getLength() < minLength) {
                        minLength = distance.getLength();
                        minDistance = distance;
                        blockSideActuallyUse = blockSideToCheck;
                        blockIndex = i;
                    }
                }
            }

            if (blockSideToCheck != Block::SIDE::UNKNOWN) {
                if (doCollideVector2DAndBlockCorner(ball, blocks.at(i), blockSideToCheck, &distance, &whichCorner)) {
                    if (distance.getLength() < minLength) {
                        minLength = distance.getLength();
                        minDistance = distance;
                        blockSideActuallyUse = whichCorner;
                        blockIndex = i;
                    }
                }
            }

            Block::SIDE blockSideToCheck = Block::SIDE::UNKNOWN;

            if (ballDir == E_UP       ||
                ballDir == E_RIGHT_UP ||
                ballDir == E_LEFT_UP) {
                blockSideToCheck = Block::SIDE::DOWNER;
            } else if (ballDir == E_DOWN       ||
                       ballDir == E_RIGHT_DOWN ||
                       ballDir == E_LEFT_DOWN) {
                blockSideToCheck = Block::SIDE::UPPER;
            }

            if (blockSideToCheck != Block::SIDE::UNKNOWN) {
                if (doCollideVector2DAndBlock(ball, blocks.at(i), blockSideToCheck, &distance)) {
                    if (distance.getLength() < minLength) {
                        minLength = distance.getLength();
                        minDistance = distance;
                        blockSideActuallyUse = blockSideToCheck;
                        blockIndex = i;
                    }
                }
            }

            if (blockSideToCheck != Block::SIDE::UNKNOWN) {
                if (doCollideVector2DAndBlockCorner(ball, blocks.at(i), blockSideToCheck, &distance, &whichCorner)) {
                    if (distance.getLength() < minLength) {
                        minLength = distance.getLength();
                        minDistance = distance;
                        blockSideActuallyUse = whichCorner;
                        blockIndex = i;
                    }
                }
            }
        }

        if (minLength != FLT_MAX) {
            // collision occurred
            if (((blockSideActuallyUse == Block::SIDE::RIGHTER) && (tempBall.getSpeedX() < 0)) ||
                ((blockSideActuallyUse == Block::SIDE::LEFTER)  && (tempBall.getSpeedX() > 0))) {
                float newSpeedX = tempBall.getSpeedX() - minDistance.getVector().getTerminal().x;
                float newSpeedY = tempBall.getSpeedY() * (newSpeedX / tempBall.getSpeedX());
                Kona::Vector newVector(Kona::Point(-1 * newSpeedX, newSpeedY));
                tempBall.setPosition(current_position.x + minDistance.getVector().getTerminal().x,
                                     current_position.y + minDistance.getVector().getTerminal().y);
                tempBall.setVector(newVector);
                BALL_REFLECT_X();
                onCollisionBallAndBlock(blockIndex, true);
                continue;
            } else if (((blockSideActuallyUse == Block::SIDE::UPPER)  && (tempBall.getSpeedY() < 0)) ||
                       ((blockSideActuallyUse == Block::SIDE::DOWNER) && (tempBall.getSpeedY() > 0))) {
                float newSpeedY = tempBall.getSpeedY() - minDistance.getVector().getTerminal().y;
                float newSpeedX = tempBall.getSpeedX() * (newSpeedY / tempBall.getSpeedY());

                Kona::Vector newVector(Kona::Point(newSpeedX, -1 * newSpeedY));
                tempBall.setPosition(current_position.x + minDistance.getVector().getTerminal().x,
                                     current_position.y + minDistance.getVector().getTerminal().y);
                tempBall.setVector(newVector);
                BALL_REFLECT_Y();
                onCollisionBallAndBlock(blockIndex, true);
                continue;
            } else if (blockSideActuallyUse == Block::SIDE::CORNER_LEFTER_DOWNER  ||
                       blockSideActuallyUse == Block::SIDE::CORNER_LEFTER_UPPER   ||
                       blockSideActuallyUse == Block::SIDE::CORNER_RIGHTER_DOWNER ||
                       blockSideActuallyUse == Block::SIDE::CORNER_RIGHTER_UPPER) {
                float newAngle = calcReflectAngleByCollideCorner(ball->getVector2D().getAngle(), blockSideActuallyUse);
                float newSpeed = tempBall.getSpeed() - minDistance.getLength();
                tempBall.setPosition(minDistance.getTerminalPosition().x, 
                                     minDistance.getTerminalPosition().y);
                tempBall.setVector(Kona::Vector(newSpeed, newAngle));
                ball->setVector(Kona::Vector(ball->getSpeed(), newAngle));
                onCollisionBallAndBlock(blockIndex, true);
                continue;
            }
        }

        if (doCollideBallAndBar(tempBall) ||
            isBallNearWhileBarSwinging(*bar, tempBall)) {
            if (calcCollisionBallAndBar(tempBall)) {
                continue;
            }
        }

        // check collision to window edge
        // width edge check
        if (tempBall.getSpeedX() > 0) {
            if (width <= current_position.x + tempBall.getSpeedX() + radius) {
                // turn over
                float newSpeedX = width - (current_position.x + tempBall.getSpeedX() + radius);
                float newSpeedY = tempBall.getSpeedY() * (-1 * newSpeedX / tempBall.getSpeedX());
                Kona::Vector newVector(Kona::Point(newSpeedX, newSpeedY));
                tempBall.setPosition(current_position.x + tempBall.getSpeedX() - newSpeedX,
                                     current_position.y + tempBall.getSpeedY() - newSpeedY);
                tempBall.setVector(newVector);
                BALL_REFLECT_X();
                continue;
            }
        } 

        if (tempBall.getSpeedX() < 0) {
            if (0 >= current_position.x - (-1 * tempBall.getSpeedX()) - radius) {
                // turn over
                float newSpeedX = current_position.x - (-1 * tempBall.getSpeedX()) - radius;
                float newSpeedY = tempBall.getSpeedY() * (-1 * newSpeedX / tempBall.getSpeedX());
                Kona::Vector newVector(Kona::Point(-1 * newSpeedX, newSpeedY));
                tempBall.setPosition(current_position.x + tempBall.getSpeedX() - newSpeedX,
                                     current_position.y + tempBall.getSpeedY() - newSpeedY);
                tempBall.setVector(newVector);
                BALL_REFLECT_X();
                continue;
            }
        }

        // height edge (top) check
        if (tempBall.getSpeedY() > 0) {
            if (height <= current_position.y + tempBall.getSpeedY() + radius) {
                // turn over
                float newSpeedY = height - (current_position.y + tempBall.getSpeedY() + radius);
                float newSpeedX = tempBall.getSpeedX() * (newSpeedY / tempBall.getSpeedY());
                Kona::Vector newVector(Kona::Point(newSpeedX, newSpeedY));
                tempBall.setPosition(current_position.x + tempBall.getSpeedX() - newSpeedX,
                                     current_position.y + tempBall.getSpeedY() + newSpeedY);
                tempBall.setVector(newVector);
                BALL_REFLECT_Y();
                continue;
            }
        }

        // height edge (bottom) check
        if (0 >= current_position.y - tempBall.getSpeedY() - radius) {
            eventNotify(ModelManagerEventListener::ModelManagerEvent::BALL_FALL, NULL);
            return;
        }

        Position new_position;
        new_position.x = current_position.x + tempBall.getSpeedX();
        new_position.y = current_position.y + tempBall.getSpeedY();

        ball->setPosition(new_position);
        break;
    }
    
}


void
ModelManager::eventNotify(ModelManagerEventListener::ModelManagerEvent in_event, void* arg) {
    for (ModelManagerEventListener* listener : listeners) {
        listener->onModelManagerEvent(in_event, arg);
    }
}

bool
ModelManager::shouldSwingBar(int in_angle) {
    if (in_angle < -90) {
        return true;
    }
    return false;
}

void
ModelManager::startSwinging() {
    bar->startSwinging();
    barSwingElapsedFrame = 0;
    currentSwingState = 0;
    barFollowthroughElapsedFrame = 0;
    eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING_START, NULL);
}

void
ModelManager::endSwinging() {
    bar->endSwinging();
    isAlreadyHitBySwing = false;
    barSwingElapsedFrame = 0;
    currentSwingState = 0;
    barFollowthroughElapsedFrame = 0;
    eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING_END, NULL);
}

template<class T, size_t N>
size_t array_size(T (&)[N]) { return N; }

bool
ModelManager::isTimeToFollowThrough(int in_currentSwingState) {
    bool isTimeToFollowThrough = in_currentSwingState == (array_size(swingBarAngleTable) - 1);
    return isTimeToFollowThrough;
}

void
ModelManager::progressBarSwinging() {
    // control bar rotation according to elapsed time
    // until start of swinging.

    int transitionThreshold = 1; // increase if swing should be more slow
    barSwingElapsedFrame++;

    if (barSwingElapsedFrame > transitionThreshold) {
        barSwingElapsedFrame = 0;
        int barAngle;
        if (isTimeToFollowThrough(currentSwingState)) {
            // stop until elpase time for follow through
            int followThroughFrame = 10;
            barFollowthroughElapsedFrame++;
            if (barFollowthroughElapsedFrame > followThroughFrame) {
                currentSwingState++; // End of swing
            }
        } else {
            barAngle = swingBarAngleTable[currentSwingState++];
            bar->setAngle(barAngle);
            eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWINGING, &barAngle);
        }

        if (currentSwingState == array_size(swingBarAngleTable)) {
            endSwinging();
        }
    }
}

bool
ModelManager::doCollideWhileBarSwinging(Position in_ballPosition, Position in_barPosition, int* out_angleAtHit) {

    double radian = std::atan2(in_ballPosition.y - in_barPosition.y,
                               in_ballPosition.x - (in_barPosition.x - (bar->getWidth() / 2)));
    // FIXME: should treat as a method to get current bar angle
    float degreeBallAndBar = radian * 180 / M_PI;

    if (degreeBallAndBar > swingBarAngleTable[currentSwingState - 1] &&
        degreeBallAndBar <= swingBarAngleTable[currentSwingState]) {
        *out_angleAtHit = degreeBallAndBar;
        return true;
    }

    return false;
}

static int
distanceOfBallFromBar (Ball& in_ball, Bar& in_bar, int in_currentBarAngle) {

    Kona::Point ball_p (in_ball.getPosition().x - (in_bar.getPosition().x - in_bar.getWidth() / 2) + in_ball.getRadius(),
                        in_ball.getPosition().y - in_bar.getPosition().y);
    Kona::Vector bar_v (Kona::Point (in_bar.getWidth(), in_currentBarAngle));

    return bar_v.distance (ball_p);
}

static float
calculateCrossOfBallAndBar(Ball& in_ball, Bar &in_bar) {
    Kona::Vector ball_v = in_ball.getVector();
    Kona::Vector2D stretchedBar = in_bar.getVector2DOfBar().getStrechedVector(in_ball.getRadius());
    Kona::Vector bar_v(stretchedBar.getLength(), in_bar.getAngle());
    return bar_v.cross (ball_v) / bar_v.getLength();
}

static float
calcReflectAngleByBarState(Ball in_ball, Bar in_bar) {
    int unitLength = 1;
    float currentBallAngle = in_ball.getVector2D().getAngle();
    float ballCross = calculateCrossOfBallAndBar (in_ball, in_bar);
    Kona::Vector v(unitLength, currentBallAngle);

    int currentBarAngle = in_bar.getAngle();
    if (ballCross < 0) {
        v += Kona::Vector(Kona::Vector(std::abs(ballCross * 2), currentBarAngle + 90));
    } else if (ballCross > 0) {
        v += Kona::Vector(Kona::Vector(std::abs(ballCross * 2), currentBarAngle - 90));
    } else {
        v += Kona::Vector(Kona::Vector(unitLength * 2, currentBallAngle + 180));
    }
    return v.getAngle();
}

void
ModelManager::calcBallReflectionBySwing(Ball& inout_ball) {

    if (ball->getSpeed() == 0) {
        int hitSpeed = 10;
        ball->addVector(Kona::Vector(hitSpeed, bar->getAngle() + 90));
        return;
    }

    Kona::Point intersectPoint = Kona::Point(inout_ball.getPosition().x,
                                             inout_ball.getPosition().y);

    Kona::Vector2D distanceVector(inout_ball.getVector2D().getStartPosition(), intersectPoint);
    float newAngle = calcReflectAngleByBarState(*ball, *bar);
    float newSpeed = inout_ball.getSpeed();
    inout_ball.setPosition(intersectPoint.x, intersectPoint.y);
    inout_ball.setSpeed(newSpeed);
    inout_ball.setDirection(newAngle);
    float ballCross = calculateCrossOfBallAndBar (*ball, *bar);
    ball->addVector(Kona::Vector(-1 * ballCross * 2, bar->getAngle() + 90));
}

void
ModelManager::calcBallReflection(Ball& inout_ball) {

    Kona::Point intersectPoint;
    Kona::Vector2D barVector2d = bar->getVector2DOfBar();
    Kona::Vector2D stretchedVector2D = barVector2d.getStrechedVector(inout_ball.getRadius());
    inout_ball.getVector2D().calcIntersectPoint(stretchedVector2D, &intersectPoint);

    Kona::Vector2D distanceVector(inout_ball.getVector2D().getStartPosition(), intersectPoint);
    float newAngle = calcReflectAngleByBarState(*ball, *bar);
    float newSpeed = inout_ball.getSpeed() - distanceVector.getLength();
    inout_ball.setPosition(intersectPoint.x, intersectPoint.y);
    inout_ball.setSpeed(newSpeed);
    inout_ball.setDirection(newAngle);
    float ballCross = calculateCrossOfBallAndBar (*ball, *bar);
    ball->addVector(Kona::Vector(-1 * ballCross * 2, bar->getAngle() + 90));
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

    currentSwingState = 0;
    isAlreadyHitBySwing = false;

    isDrawing = false;
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

bool
ModelManager::calcCollisionBallAndBar(Ball& in_ball) {
    Position ballPosition = in_ball.getPosition();
    Position barPosition = bar->getPosition();

    if (bar->isSwinging()) {
        if (isAlreadyHitBySwing) {
            return false;
        }

        int hitAngle;
        if (doCollideWhileBarSwinging(ballPosition, barPosition, &hitAngle)) {
            isAlreadyHitBySwing = true;
            bar->setAngle(hitAngle);
            calcBallReflectionBySwing(in_ball);
            eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING_AT_HIT, &hitAngle);
            return true;
        }
        return false;
    }

    calcBallReflection(in_ball);
    return true;
}

void
ModelManager::initializeBar() {
    // init bar position
#if 1
    bar->setPosition(field->getWidth() / 2, field->getHeight() / 4);
#else // for testing
    bar->setPosition(field->getWidth() / 2, field->getHeight() / 4);
    bar->setWidth(field->getWidth());
#endif
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

int
ModelManager::getBarAngle() {
    return bar->getAngle();
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
}

void
ModelManager::setFieldSize(int in_width, int in_height) {
    field->setFieldSize(in_width, in_height);
}

void
ModelManager::initializeBlocks() {
#ifndef TEST
    // ToDo: should refer configuration for blocks initialization.
    int numOfBlocksPerLine = 6;
    int lineNumOfBlocks = 6;
    int blockWidth = field->getWidth() / numOfBlocksPerLine;
    int blockHeight = 30;
    int fieldHeight = field->getHeight();
    int fieldWidth = field->getWidth();
#else // for testing
    int numOfBlocksPerLine = 1;
    int lineNumOfBlocks = 1;
    int blockWidth = 50;
    int blockHeight = 50;
    int fieldHeight = field->getHeight();
    int fieldWidth = field->getWidth();
#endif

    for (int j = 0; j < lineNumOfBlocks; j++) {
        for (int i = 0; i < numOfBlocksPerLine; i++) {
            Block* block = new Block();
            block->setSize(blockWidth, blockHeight);
#ifndef TEST
            block->setPosition((i * blockWidth) + (blockWidth / 2 ),
                               fieldHeight - (blockHeight / 2) - (blockHeight * j) - 50);
            block->setLife(1);
#else // for testing
            block->setPosition(fieldWidth / 2,
                               fieldHeight / 2);
            block->setLife(256);
#endif
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

bool
ModelManager::doCollideBallAndBar(Ball in_ball) {

    if (bar->isSwinging()) {
        return false;
    }

    int currentBarAngle = bar->getAngle();
    float ballCross = calculateCrossOfBallAndBar (in_ball, *bar);
    if (ballCross > 0) {
        return false;
    }

    static int count = 0;
    Kona::Point intersectPoint;
    Kona::Vector2D stretchedBar = bar->getVector2DOfBar().getStrechedVector(in_ball.getRadius());
    if (in_ball.getVector2D().calcIntersectPoint(stretchedBar, &intersectPoint)) {
        return true;
    }
    return false;
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
}

void
ModelManager::addModelManagerEventListener(ModelManagerEventListener* in_listener) {
    listeners.push_back(in_listener);
}

void
ModelManager::setBarPositionX(int in_x) {
    lastTouchedPosition.x = in_x;

    if (isTouchOnRightSideOfBar(in_x)) {
        bar->setDirection(BarDirection::RIGHT);
    } else {
        bar->setDirection(BarDirection::LEFT);
    }
}

void
ModelManager::setBallPositionX(int in_x) {
    Position p;
    p.x = in_x;
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
    if (bar->isSwinging()) {
        return;
    }

    verticalDrawStart.y = in_y;
    verticalDrawEnd.y = in_y;
    bar->setAngle(getVerticalDrawDelta());
}

void
ModelManager::updateVerticalDraw(int in_y) {
    if (bar->isSwinging()) {
        return;
    }

    verticalDrawEnd.y = in_y;

    // if draw towards upper, update start position
    // not to stack "debt" of vetical draw.
    if (verticalDrawEnd.y > verticalDrawStart.y) {
        verticalDrawStart.y = verticalDrawEnd.y;
    }
    bar->setAngle(getVerticalDrawDelta());
}

static int
calculateVerticalDrawDelta(int start, int end) {
    return end - start;
}

void
ModelManager::endVerticalDraw() {
    if (bar->isSwinging()) {
        return;
    }

    int delta = calculateVerticalDrawDelta(verticalDrawStart.y, verticalDrawEnd.y);
    if (shouldSwingBar(delta)) {
        startSwinging();
    }

    verticalDrawStart.y = 0;
    verticalDrawEnd.y = 0;
    bar->setAngle(getVerticalDrawDelta());
}

int
ModelManager::getVerticalDrawDelta() {
    int delta = calculateVerticalDrawDelta(verticalDrawStart.y, verticalDrawEnd.y);
    
    if (delta > 0) {
        return 0;
    } else if (delta < -135) {
        return -135;
    }

    return delta;
}

bool
ModelManager::barSwinging() {
    return bar->isSwinging();
}

void
ModelManager::startDraw(Position& in_position) {
    Kona::Point touched_point(in_position.x, in_position.y);

    auto ball_position = ball->getPosition();
    Kona::Point ball_point(ball_position.x, ball_position.y);

    auto distance = Kona::Vector2D(touched_point, ball_point).getLength();
    if (distance < 50) {
        std::cout << "start to draw" << std::endl;
        // start draw callback
        initialDrawPoint = touched_point;
        lastDrawPoint = touched_point;
        eventNotify(ModelManagerEventListener::ModelManagerEvent::BALL_DRAW_START, NULL);
        isDrawing = true;
    }
}

void
ModelManager::updateDraw(Position& in_position) {
    if (!isDrawing) {
        return;
    }

    Kona::Point touched_point(in_position.x, in_position.y);
    lastDrawPoint = touched_point;
}

void
ModelManager::endDraw() {
    if (!isDrawing) {
        return;
    }

    isDrawing = false;

    Kona::Vector2D drawResult(initialDrawPoint, lastDrawPoint);

    Kona::Vector2D ballVector2D;
    ballVector2D.setLength(drawResult.getLength());
    ballVector2D.setAngle(drawResult.getAngle() + 180);

    //ball->setSpeed(ballVector2D.getLength());
    ball->setSpeed(10);
    ball->setDirection(ballVector2D.getAngle());

    eventNotify(ModelManagerEventListener::ModelManagerEvent::BALL_DRAW_END, NULL);
}

