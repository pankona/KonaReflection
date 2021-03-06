#include "TitleControl.h"
#include <stdio.h>

// private methods

void
TitleControl::notifySceneEnd() {
    for (SceneEndListener* listener : listeners) {
        log ("[TitleControl] notifySceneEnd");
        listener->onSceneEnd();
    }
}

// public methods

void
TitleControl::initialize(Scene* baseScene) {
    tvm.initialize(baseScene);
    tvm.addViewManagerEventListener(this);

    Size screenSize = Director::getInstance()->getVisibleSize();
    tvm.initializeTitle((int) screenSize.width, (int) screenSize.height);
}

void
TitleControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {
    log ("[%s] event fired", __func__);
    notifySceneEnd();
}

void
TitleControl::addSceneEndListener(SceneEndListener* in_listener) {
    listeners.push_back(in_listener);
}
