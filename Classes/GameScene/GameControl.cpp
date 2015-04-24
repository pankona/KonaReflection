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
    mm.progress(delta);

    // these should be treated on callback from model manager.
    vm.setBarPosition(mm.getBarPosition());
    vm.setBallPosition(mm.getBallPosition());

    collidedBlockNum = 0;
    vm.updateView();
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
    log ("bar initialized with parameter: w = %d, h = %d, p = (%d, %d)", mm.getBarWidth(), mm.getBarHeight(), mm.getBarPosition().x, mm.getBarPosition().y);

    mm.initializeBall();
    vm.initializeBall(mm.getBallRadius(), mm.getBallPosition());
    log ("ball initialized with parameter: r = %d, p = (%d, %d)", mm.getBallRadius(), mm.getBallPosition().x, mm.getBallPosition().y);

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
}

void
GameControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {

    Position *p;

    if (gameState == GameState::READY) {
        switch (in_event) {
            case ViewManagerEvent::TOUCH_BEGAN:
            case ViewManagerEvent::TOUCH_MOVED:
                p = (Position*) arg;
                mm.setBallAndBarPositionX(p->x);
                break;
            case ViewManagerEvent::TOUCH_ENDED:
                gameState = GameState::STARTED;
                mm.setBallSpeed(10); // Fix me: should refer configuration
                break;
            default:
                break;
        }

        return;

    } else if (gameState == GameState::STARTED) {

        switch (in_event) {
            case ViewManagerEvent::BALL_AND_BAR_COLLISION:
                mm.onCollisionBallAndBar();
                break;
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
            case ViewManagerEvent::BALL_AND_BLOCK_COLLISION:
                int* blockIndex;
                blockIndex = (int*) arg;

                // only one time ball can turn over by block per one frame.
                // ToDo: this logic should be move to model manager.
                bool needBallTurnOver;
                if (collidedBlockNum == 0) {
                    needBallTurnOver = true;
                } else {
                    needBallTurnOver = false;
                }
                mm.onCollisionBallAndBlock(*blockIndex, needBallTurnOver);
                collidedBlockNum++;
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

    switch (in_event) {
        case ModelManagerEvent::BLOCK_DIED:
            int* blockIndex;
            blockIndex = (int *)arg;
            vm.markBlockAsKilled(*blockIndex);
            break;
        case ModelManagerEvent::ALL_BLOCK_DESTROYED:
            mm.setBallSpeed(0);
            vm.removeBall();
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
