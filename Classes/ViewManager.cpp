#include "ViewManager.h"

ViewManager::ViewManager() {
}

void
ViewManager::initialize(Scene* baseScene) {

    // initialize model manager
    mm.initialize();

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    mm.getField()->setFieldSize((int)screenSize.width, (int)screenSize.height);

    // field configuration
    dField = new DrawableField(mm.getField());
    dField->createDrawNode();
    baseScene->addChild(dField->getDrawNode());

    // ball configuration
    dBall = new DrawableBall();
    dBall->createDrawNode();
    baseScene->addChild(dBall->getDrawNode());
    mm.getField()->addBall(dBall->getBall());

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

