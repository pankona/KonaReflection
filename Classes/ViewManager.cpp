#include "ViewManager.h"
#include <stdio.h>

// private methods
void
ViewManager::updateView() {
    dBall->updatePosition();
    dBar->updatePosition();

    Rect ballRect = dBall->getSprite()->getBoundingBox();
    Rect barRect = dBar->getSprite()->getBoundingBox();
    if (ballRect.intersectsRect(barRect)) {
        mm.getField()->onCollisionBallAndBar();
    }

}

// public methods

void
ViewManager::initialize(Scene* baseScene) {

    // initialize model manager
    mm.initialize();

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    mm.getField()->setFieldSize((int)screenSize.width, (int)screenSize.height);
    log ("set screen size w = %d, h = %d", (int)screenSize.width, (int)screenSize.height);

    // field configuration
    dField = new DrawableField(mm.getField());
    baseScene->addChild(dField->getSprite());

    // ball configuration
    dBall = new DrawableBall();
    baseScene->addChild(dBall->getSprite());
    mm.getField()->addBall(dBall->getBall());

    // bar configuration
    dBar = new DrawableBar();
    baseScene->addChild(dBar->getSprite());
    mm.getField()->setBar(dBar->getBar());
}

void
ViewManager::progress(float delta) {
    mm.progress(delta);
    updateView();
}


