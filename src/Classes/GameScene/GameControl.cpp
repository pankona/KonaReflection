#include "GameControl.h"
#include <stdio.h>

void
GameControl::notifySceneEnd() {
    for (SceneEndListener* listener : listeners) {
        log ("[TitleControl] notifySceneEnd");
        listener->onSceneEnd();
    }
}

void
GameControl::update(float delta) {

    if (needStop) {
        stopCount--;
        if (stopCount <= 0) {
            needStop = false;
        }
        return;
    }

    mm.progress(delta);

    if (gameState == GameState::READY) {
        mm.setBallPositionX(mm.getBarPosition().x);
    }

    // these should be treated on callback from model manager.
    vm.setBarPosition(mm.getBarPosition());
    vm.setBallPosition(mm.getBallPosition());
    vm.setBarRotation(mm.getBarAngle());
}

void
GameControl::dispatchTimerEvent(int* in_desc) {
    Size screenSize = Director::getInstance()->getVisibleSize();
    switch (*in_desc) {
        case ModelManagerEvent::ALL_BLOCK_DESTROYED:
            log ("all blocks are destroyed! congratulation!");
            vm.showCongratulation((int)screenSize.width, (int)screenSize.height);
            break;
        case ModelManagerEvent::PLAYER_DEAD:
            log ("Player dead. gameover.");
            vm.showGameOver((int)screenSize.width, (int)screenSize.height);
            break;
        default:
            break;
    }
}

void
GameControl::initialize(Scene* baseScene) {
    gameState = GameState::READY;

    mm.initialize();
    mm.addModelManagerEventListener(this);
    vm.initialize(baseScene);
    vm.addViewManagerEventListener(this);

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    vm.initializeField((int) screenSize.width, (int) screenSize.height);
    mm.setFieldSize((int) screenSize.width, (int) screenSize.height);
    log ("set screen size w = %d, h = %d", (int) screenSize.width, (int) screenSize.height) ;

    mm.initializeBar();
    vm.initializeBar(mm.getBarWidth(), mm.getBarHeight(), mm.getBarPosition());
    log ("bar initialized with parameter: w = %d, h = %d, p = (%d, %d)",
         mm.getBarWidth(), mm.getBarHeight(), (int) mm.getBarPosition().x, (int) mm.getBarPosition().y);

    mm.initializeBall();
    vm.initializeBall(mm.getBallRadius(), mm.getBallPosition());
    log ("ball initialized with parameter: r = %d, p = (%d, %d)",
         mm.getBallRadius(), (int) mm.getBallPosition().x, (int) mm.getBallPosition().y);

    mm.initializeBlocks();
    for (int i = 0; i < mm.getBlockNum(); i++) {
        vm.addBlock(mm.getBlockWidth(i), mm.getBlockHeight(i), mm.getBlockPosition(i));

        // temporary implementation. set colors to blocks.
        switch (i % 4) {
            case 0:
                vm.setBlockColor(i, Color3B::BLUE);
                break;
            case 1:
                vm.setBlockColor(i, Color3B::MAGENTA);
                break;
            case 2:
                vm.setBlockColor(i, Color3B::GRAY);
                break;
            case 3:
                vm.setBlockColor(i, Color3B::ORANGE);
                break;
            default:
                vm.setBlockColor(i, Color3B::BLACK);
                break;
        }
    }

    needStop = false;
    stopCount = 0;
}

void
GameControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {

    Position *p;

    if (gameState == GameState::READY) {
        switch (in_event) {
            case ViewManagerEvent::TOUCH_BEGAN:
                p = (Position*) arg;
                mm.startDraw(*p);
                break;
            case ViewManagerEvent::TOUCH_MOVED:
                p = (Position*) arg;
                mm.updateDraw(*p);
                break;
            case ViewManagerEvent::TOUCH_ENDED:
                mm.endDraw();
                break;
            default:
                break;
        }

        return;

    } else if (gameState == GameState::STARTED) {

        switch (in_event) {
            case ViewManagerEvent::TOUCH_BEGAN:
                p = (Position*) arg;
                mm.onTouchBegan(p->x, p->y);
                break;
            case ViewManagerEvent::TOUCH_MOVED:
                p = (Position*) arg;
                mm.onTouchMoved(p->x, p->y);
                break;
            case ViewManagerEvent::TOUCH_ENDED:
                mm.onTouchEnded();
                break;
            default:
                break;
        }

        return;

    } else if (gameState == GameState::GAMEOVER) {

        switch (in_event) {
            case ViewManagerEvent::BACK_TO_TITLE:
                log ("[%s] notifySceneEnd call.", __FILE__);
                notifySceneEnd();
                break;
            case ViewManagerEvent::GO_TO_NEXT_STAGE:
                // ToDo: implement
                break;
            case ViewManagerEvent::TIMER_EXPIRED:
                dispatchTimerEvent((int*)arg);
                break;
            default:
                break;
        }

        return;
    }
}

void
GameControl::onModelManagerEvent(ModelManagerEvent in_event, void* arg) {

    int delay_time_sec;
    int* barAngle;

    switch (in_event) {
        case ModelManagerEvent::BALL_DRAW_END:
            gameState = GameState::STARTED;
            break;
        case ModelManagerEvent::BLOCK_DIED:
            int* blockIndex;
            blockIndex = (int *)arg;
            vm.markBlockAsKilled(*blockIndex);
            break;
        case ModelManagerEvent::ALL_BLOCK_DESTROYED:
            mm.setBallSpeed(0);
            vm.removeBall();
            mm.resetBall();
            // FIXME: should not set model manager event to view manager.
            // then game control needs to be notified model manager event from view manager.
            delay_time_sec = 1;
            vm.setTimer(delay_time_sec, (int) ModelManagerEvent::ALL_BLOCK_DESTROYED);
            gameState = GameState::GAMEOVER;
            break;
        case ModelManagerEvent::BALL_FALL:
            mm.decreasePlayerLife();
            mm.setBallSpeed(0);

            if (mm.isPlayerStillAlive()) {
                gameState = GameState::READY;
                mm.resetBall();
            } else {
                gameState = GameState::GAMEOVER;
                vm.removeBall();
                mm.resetBall();
                delay_time_sec = 1;
                vm.setTimer(delay_time_sec, (int) ModelManagerEvent::PLAYER_DEAD);
            }
            break;
        default:
            break;
    }
}

void
GameControl::addSceneEndListener(SceneEndListener* in_listener) {
    listeners.push_back(in_listener);
}
