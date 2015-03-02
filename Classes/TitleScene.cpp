#include "TitleScene.h"

USING_NS_CC;

// private methods

void
TitleScene::notifySceneEnd() {
    for (SceneEndListener* listener : listeners) {
        listener->onSceneEnd();
    }
}

// public methods

bool
TitleScene::init() {
    if (!Scene::init()) {
        return false;
    }

    titleControl.initialize(this);
    titleControl.addSceneEndListener(this);

    return true;
}

void
TitleScene::addSceneEndListener(SceneEndListener* in_listener) {
    listeners.push_back(in_listener);
}

void
TitleScene::onSceneEnd() {
    notifySceneEnd();
}
