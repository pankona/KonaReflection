#include "ViewManager.h"

ViewManager::ViewManager() {
}

void
ViewManager::initialize(Scene* baseScene) {

    // initialize model manager
    mm.initialize();

    // ball configuration
    dBall = new DrawableBall();
    dBall->createDrawNode();
    baseScene->addChild(dBall->getDrawNode());
    mm.getField()->addBall(dBall->getBall());

    // set screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    mm.getField()->setFieldSize((int)screenSize.width, (int)screenSize.height);
}

void
ViewManager::progress(float delta) {
    mm.progress(delta);
    updateView();
}

void
ViewManager::updateView() {
    dBall->updatePosition();
}

