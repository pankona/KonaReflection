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
    currentScene = TITLE;
}

void
SceneManager::onSceneEnd() {
    // keep currentScene to destroy later
    auto sceneToBeDestroyed = scene;

    // go to next scene
    switch (currentScene) {
        case TITLE:
            scene = BaseScene::create();
            ((BaseScene*)scene)->addSceneEndListener(this);
            currentScene = GAME;
            break;
        case GAME:
            scene = TitleScene::create();
            ((TitleScene*)scene)->addSceneEndListener(this);
            currentScene = TITLE;
            break;


    }
    auto transition = TransitionFade::create(0.5, scene);
    Director::getInstance()->replaceScene(transition);

    // ToDo: destroy current scene
}
