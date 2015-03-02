#include "SceneManager.h"
#include "TitleScene.h"

USING_NS_CC;

void
SceneManager::initialize() {

    auto director = Director::getInstance();
    auto scene = TitleScene::create();
    director->runWithScene(scene);
}
