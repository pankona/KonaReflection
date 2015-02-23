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

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    log ("set screen size w = %d, h = %d", (int) screenSize.width, (int) screenSize.height) ;

    vm.initializeBar(mm.getBarWidth(), mm.getBarHeight(), mm.getBarInitialPosition());
    vm.initializeField((int) screenSize.width, (int) screenSize.height, mm.getFieldInitialPosition());
    vm.initializeBall(mm.getBallRadius(), mm.getBallInitialPosition());
}
