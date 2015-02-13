#include "SplashScene.h"
#include "DrawableBall.h"

USING_NS_CC;

Scene*
Splash::createScene() {
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool
Splash::init() {
    if (!Layer::init()) {
        return false;
    }

    initializeSprites();

    scheduleUpdate();
    return true;
}

void
Splash::update(float delta) {
    gameControl.update(delta);
}

void
Splash::initializeSprites() {

    DrawableBall* dBall = new DrawableBall();
    dBall->createDrawNode();
    this->addChild(dBall->getDrawNode());

    gameControl.addDBall(dBall);
}
