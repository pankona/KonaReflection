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

    configureField();
    scheduleUpdate();
    return true;
}

void
Splash::update(float delta) {
    field.progress(delta);
}

void
Splash::configureField() {
    DrawableBall* dBall = new DrawableBall();
    dBall->createDrawNode();
    this->addChild(dBall->getDrawNode());
    field.addDBall(dBall);
}
