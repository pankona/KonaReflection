#include "SplashScene.h"
#include "DrawableBall.h"
#include <iostream>

USING_NS_CC;

bool
Splash::init() {
    if (!Scene::init()) {
        return false;
    }

    // Initialize Layers and Models
    gameControl.initialize(this);

    scheduleUpdate();
    return true;
}

void
Splash::update(float delta) {
    gameControl.update(delta);
}
