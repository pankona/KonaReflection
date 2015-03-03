#include "SceneManager.h"
#include "TitleScene.h"

USING_NS_CC;

void
SceneManager::initialize() {

    auto director = Director::getInstance();
    scene = TitleScene::create();
    ((TitleScene*)scene)->addSceneEndListener(this);
    director->runWithScene(scene);
}

void
SceneManager::onSceneEnd() {
    log ("[%s] on scene end.", __func__);
}
