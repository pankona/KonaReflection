#ifndef __BASESCENE_H__
#define __BASESCENE_H__

#include "cocos2d.h"
#include "GameControl.h"
#include "SceneEndListener.h"

USING_NS_CC;

class BaseScene : public Scene, public SceneEndListener {
private:
    GameControl gameControl;
    std::vector<SceneEndListener*> listeners;
    void notifySceneEnd();

public:
    virtual bool init();
    virtual void update(float delta);
    void onSceneEnd();
    void addSceneEndListener(SceneEndListener*);
    CREATE_FUNC(BaseScene);
};

#endif // __BASESCENE_H__
