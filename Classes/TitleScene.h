#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
#include "TitleControl.h"
#include "SceneEndListener.h"

USING_NS_CC;

class TitleScene : public Scene, public SceneEndListener {
private:
    std::vector<SceneEndListener*> listeners;
    TitleControl titleControl;
    void notifySceneEnd();

public:
    virtual bool init();
    void onSceneEnd();
    void addSceneEndListener(SceneEndListener*);
    CREATE_FUNC(TitleScene);
};

#endif // __TITLESCENE_H__
