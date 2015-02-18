#include "ViewManager.h"

// private methods
void
ViewManager::updateView() {
    dBall->updatePosition();
}

// public methods

void
ViewManager::initialize(Scene* baseScene) {

    // initialize model manager
    mm.initialize();

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    mm.getField()->setFieldSize((int)screenSize.width, (int)screenSize.height);

    // field configuration
    dField = new DrawableField(mm.getField());
    baseScene->addChild(dField->getDrawNode());

    // ball configuration
    dBall = new DrawableBall();
    baseScene->addChild(dBall->getDrawNode());
    mm.getField()->addBall(dBall->getBall());

    // bar configuration
    dBar = new DrawableBar();
    baseScene->addChild(dBar->getDrawNode());
    mm.getField()->setBar(dBar->getBar());
}

void
ViewManager::progress(float delta) {
    mm.progress(delta);
    updateView();
}


