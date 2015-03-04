#include "SceneManager.h"
#include "TitleScene.h"
#include "BaseScene.h"

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
    auto currentScene = scene;

    // go to next scene
    scene = BaseScene::create();
    auto transition = TransitionFade::create(0.5, scene);
    Director::getInstance()->replaceScene(transition);

    // ToDo: destroy current scene
}
