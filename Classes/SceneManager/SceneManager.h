#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "cocos2d.h"
#include "SceneEndListener.h"

USING_NS_CC;

class SceneManager : public SceneEndListener {
private:
    Scene* scene;
    enum CurrentScene {
        TITLE,
        GAME
    };
    CurrentScene currentScene;

public:
    void initialize();
    void onSceneEnd();
};

#endif // __SCENEMANAGER_H__
