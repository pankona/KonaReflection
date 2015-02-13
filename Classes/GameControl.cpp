
#include "GameControl.h"

void
GameControl::update(float delta) {
    field.progress(delta);
    dball->updatePosition();
}

void
GameControl::addDBall(DrawableBall* in_dball) {
    dball = in_dball;
    field.addBall(in_dball->getBall());
}

void
GameControl::initialize(cocos2d::Scene* baseScene) {
    DrawableBall* dBall = new DrawableBall();
    dBall->createDrawNode();
    baseScene->addChild(dBall->getDrawNode());

    this->addDBall(dBall);
}
