#include "GameControl.h"
#include <stdio.h>

void
GameControl::update(float delta) {
    mm.progress(delta);

    // these should be treated on callback from model manager.
    vm.setBarPosition(mm.getBarPosition());
    vm.setBallPosition(mm.getBallPosition());
    vm.updateView();
}

void
GameControl::initialize(Scene* baseScene) {
    mm.initialize();
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
}

void
GameControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {

    Position *p;

    switch (in_event) {
        case ViewManagerEvent::BAR_AND_BALL_COLLISION:
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
        default:
            break;
    }
}
