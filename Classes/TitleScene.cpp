#include "TitleScene.h"

USING_NS_CC;

bool
TitleScene::init() {
    if (!Scene::init()) {
        return false;
    }

    titleControl.initialize(this);

    return true;
}
