#include "ViewManager.h"
#include <stdio.h>

// public methods

void
ViewManager::initialize(Scene* baseScene) {

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    log ("set screen size w = %d, h = %d", (int)screenSize.width, (int)screenSize.height);

    // field configuration
    dField = new DrawableField(screenSize.width, screenSize.height);
    dField->setOnTouchCallback();
    baseScene->addChild(dField->getSprite());

    // ball configuration
    dBall = new DrawableBall(50);
    baseScene->addChild(dBall->getSprite());

    // bar configuration
    dBar = new DrawableBar(100, 20);
    baseScene->addChild(dBar->getSprite());
}

void
ViewManager::updateView() {
    Rect ballRect = dBall->getSprite()->getBoundingBox();
    Rect barRect = dBar->getSprite()->getBoundingBox();
    if (ballRect.intersectsRect(barRect)) {
        // ToDo: notify to game controller
        log ("ball and bar collistion detected.");
    }
}

void
ViewManager::setBallPosition(Position p) {
    dBall->setPosition(p);
}

void
ViewManager::setBarPosition(Position p) {
    dBar->setPosition(p);
}

void
ViewManager::onTouchBegan(int tag, Event* event, int, int) {
    log ("[VM] onTouchBegan.");
}

void
ViewManager::onTouchMoved(int tag, Event* event, int, int) {
    log ("[VM] onTouchMoved.");
}

void
ViewManager::onTouchEnded(int tag, Event* event) {
    log ("[VM] onTouchEnded.");
}
