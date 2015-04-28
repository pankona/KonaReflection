#include "BaseScene.h"

USING_NS_CC;

void
BaseScene::notifySceneEnd() {
    for (SceneEndListener* listener : listeners) {
        log ("[%s] notifySceneEnd(). listener = %p.", __FILE__, listener);
        listener->onSceneEnd();
    }
}

bool
BaseScene::init() {
    if (!Scene::init()) {
        return false;
    }

    gameControl.initialize(this);
    gameControl.addSceneEndListener(this);

    scheduleUpdate();
    return true;
}

void
BaseScene::update(float delta) {
    gameControl.update(delta);
}

void BaseScene::onSceneEnd() {
    log ("[TitleScene] onSceneEnd.");
    notifySceneEnd();
}

void BaseScene::addSceneEndListener(SceneEndListener* in_listener) {
    log ("[%s] addSceneEndListener() called. in_listener = %p.", __FILE__, in_listener);
    listeners.push_back(in_listener);
}
