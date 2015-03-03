#ifndef __TITLECONTROL_H__
#define __TITLECONTROL_H__

#include "cocos2d.h"
#include "TitleViewManager.h"
#include "ViewManagerEventListener.h"
#include "SceneEndListener.h"

USING_NS_CC;

class TitleControl : public ViewManagerEventListener {
private:
    TitleViewManager tvm;
    std::vector<SceneEndListener*> listeners;
    void notifySceneEnd();

public:
    void initialize(Scene*);
    void onViewManagerEvent(ViewManagerEventListener::ViewManagerEvent, void*);
    void addSceneEndListener(SceneEndListener*);
};

#endif // __TITLECONTROL_H__
