#include "BaseScene.h"
#include "DrawableBall.h"

USING_NS_CC;

bool
BaseScene::init() {
    if (!Scene::init()) {
        return false;
    }

    gameControl.initialize(this);

    scheduleUpdate();
    return true;
}

void
BaseScene::update(float delta) {
    gameControl.update(delta);
}
