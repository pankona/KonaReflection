#include "SplashScene.h"

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
    return true;
}

void
Splash::update(float delta) {

}

void
Splash::configureField() {
    DrawableBall dBall;
    dBall.createDrawNode();
    this->addChild(dBall.getDrawNode());
}
