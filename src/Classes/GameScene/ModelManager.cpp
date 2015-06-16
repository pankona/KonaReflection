#include "ModelManager.h"
#include "BarDirection.h"
#include <cmath>
#include <stdio.h>

// private methods

#define BALL_REFLECT_X() \
            int originalBallSpeed = ball->getSpeed(); \
            ball->addVector(Kona::Vector(Kona::Point(-1 * ball->getSpeedX() * 2, 0))); \
            ball->setSpeed(originalBallSpeed)

#define BALL_REFLECT_Y() \
            int originalBallSpeed = ball->getSpeed(); \
            ball->addVector(Kona::Vector(Kona::Point(0, -1 * ball->getSpeedY() * 2))); \
            ball->setSpeed(originalBallSpeed)

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

    if (isBarSwinging) {
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
        BALL_REFLECT_X();
    }

    // height edge (top) check
    if (height <= current_position.y + ball->getRadius() / 2) {
        // turn over
        BALL_REFLECT_Y();
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
    if (in_angle < -90) {
        return true;
    }
    return false;
}

void
ModelManager::startSwinging() {
    isBarSwinging = true;
    barSwingElapsedFrame = 0;
    currentSwingState = 0;
    barFollowthroughElapsedFrame = 0;
    eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING_START, NULL);
}

void
ModelManager::endSwinging() {
    isBarSwinging = false;
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
            eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWINGING, &barAngle);
        }

        if (currentSwingState == array_size(swingBarAngleTable)) {
            endSwinging();
        }
    }
}

bool
ModelManager::doCollisionWhileBarSwinging(Position in_ballPosition, Position in_barPosition, int* out_angleAtHit) {

    double radian = std::atan2(in_ballPosition.y - in_barPosition.y,
                               in_ballPosition.x - (in_barPosition.x - (bar->getWidth() / 2)));
    // FIXME: should treat as a method to get current bar angle
    int currentBarAngle = swingBarAngleTable[currentSwingState];
    int degreeBallAndBar = (int) (radian * 180 / M_PI);

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

#if 0
    printf ("%d, %d\n", in_ball.getPosition().x - (in_bar.getPosition().x - in_bar.getWidth() / 2) + in_ball.getRadius(),
                        in_ball.getPosition().y - in_bar.getPosition().y);
    Kona::Vector ball_p_v(ball_p);
    ball_p_v.show();
    bar_v.show();
#endif

    return bar_v.distance (ball_p);
}

static int
calculateCrossOfBallAndBar(Ball& in_ball, Bar &in_bar, int in_currentBarAngle) {
    Kona::Vector ball_v = in_ball.getVector();
    Kona::Vector bar_v(in_bar.getWidth(), in_currentBarAngle);
    return bar_v.cross (ball_v) / bar_v.getLength();
}

static bool
doBallCollideOnSideOfBar (Ball& in_ball, Bar& in_bar, int in_currentBarAngle) {

    Kona::Vector ball_v(Kona::Point(in_ball.getPosition().x - (in_bar.getPosition().x - in_bar.getWidth() / 2),
                                    in_ball.getPosition().y - in_bar.getPosition().y));
    Kona::Vector bar_v(in_bar.getWidth(), in_currentBarAngle);
    int cosx = ball_v.dot (bar_v) / bar_v.getLength();
    if (cosx < 0 || cosx > bar_v.getLength()) {
        return true;
    }
    return false;
}

void
ModelManager::calculateBallReflection(int in_currentBarAngle) {

    // temporary configuration for testing
    if (ball->getSpeed() == 0) {
        int hitSpeed = 10;
        //ball->addVector(Kona::Vector(hitSpeed, in_currentBarAngle + 90));
        ball->addVector(Kona::Vector(hitSpeed, 60));
        return;
    }

    printf ("bar angle = %d\n", in_currentBarAngle);
    printf ("current ball angle = %d\n", ball->getVector().getAngle());

    if (doBallCollideOnSideOfBar(*ball, *bar, in_currentBarAngle)) {
        BALL_REFLECT_X();
    } else {
        int ballCross = calculateCrossOfBallAndBar (*ball, *bar, in_currentBarAngle);
        //printf ("ballCross = %d\n", ballCross);
        int originalBallSpeed = ball->getSpeed();
        //printf ("original ball speed = %d\n", ball->getSpeed());
        ball->addVector(Kona::Vector(-1 * ballCross * 2, in_currentBarAngle + 90));
        //printf ("new ball speed = %d\n", ball->getSpeed());
        ball->setSpeed(originalBallSpeed);
    }

    printf ("new ball angle = %d\n\n", ball->getVector().getAngle());
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

    isBarSwinging = false;
    currentSwingState = 0;
    isAlreadyHitBySwing = false;
}

void
ModelManager::progress(float delta) {
    moveBar(delta);
    moveBall(delta);

    if (doCollideBallAndBar()) {
        onCollisionBallAndBar();
    }
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

    if (isBarSwinging) {
        if (isAlreadyHitBySwing) {
            return;
        }

        int hitAngle;
        if (doCollisionWhileBarSwinging(ballPosition, barPosition, &hitAngle)) {
            isAlreadyHitBySwing = true;
            calculateBallReflection(hitAngle);
            //setBallSpeed(10); // temporary configuration for testing
            eventNotify(ModelManagerEventListener::ModelManagerEvent::BAR_SWING_AT_HIT, &hitAngle);
        }
        return;
    }

    int currentBarAngle = getVerticalDrawDelta();
    calculateBallReflection(currentBarAngle);
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

bool
ModelManager::doCollideBallAndBar() {

    int currentBarAngle = getVerticalDrawDelta();
    int ballCross = calculateCrossOfBallAndBar (*ball, *bar, currentBarAngle);
    printf ("ball cross = %d\n", ballCross);
    if (ballCross > 0) {
        return false;
    }

    if (distanceOfBallFromBar (*ball, *bar, currentBarAngle) <= ball->getRadius() + bar->getHeight() / 2) {
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

    if (!in_needBallTurnOver) {
        return;
    }

    Position ballPosition = ball->getPosition();
    int ballRadius = ball->getRadius();

    if (ballPosition.x + ballRadius > blockPosition.x - blockWidth / 2 &&
        ballPosition.x - ballRadius < blockPosition.x + blockWidth / 2) {
        // turn over (y)
        BALL_REFLECT_Y();
    } else if (ballPosition.y + ballRadius > blockPosition.y - blockHeight / 2 &&
               ballPosition.y - ballRadius < blockPosition.y + blockHeight) {
        // turn over (x)
        BALL_REFLECT_X();
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
    if (isBarSwinging) {
        return;
    }

    verticalDrawStart.y = in_y;
    verticalDrawEnd.y = in_y;
}

void
ModelManager::updateVerticalDraw(int in_y) {
    if (isBarSwinging) {
        return;
    }

    verticalDrawEnd.y = in_y;

    // if draw towards upper, update start position
    // not to stack "debt" of vetical draw.
    if (verticalDrawEnd.y > verticalDrawStart.y) {
        verticalDrawStart.y = verticalDrawEnd.y;
    }
}

static int
calculateVerticalDrawDelta(int start, int end) {
    return end - start;
}

void
ModelManager::endVerticalDraw() {
    if (isBarSwinging) {
        return;
    }

    int delta = calculateVerticalDrawDelta(verticalDrawStart.y, verticalDrawEnd.y);
    if (shouldSwingBar(delta)) {
        startSwinging();
    }

    verticalDrawStart.y = 0;
    verticalDrawEnd.y = 0;
}

int
ModelManager::getVerticalDrawDelta() {
    int delta = calculateVerticalDrawDelta(verticalDrawStart.y, verticalDrawEnd.y);

    return -45;
#if 0
    if (delta > 0) {
        return 0;
    } else if (delta < -135) {
        return -135;
    }

    return delta;
#endif
}

bool
ModelManager::barSwinging() {
    return isBarSwinging;
}
