#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "ModelManager.h"
#include "DrawableBall.h"

USING_NS_CC;

class ViewManager {
private:    
    ModelManager mm;
    DrawableBall *dBall;
    void updateView();

public:
    ViewManager();
    void initialize(Scene* baseScene);
    void progress(float delta);
};

#endif // __VIEWMANAGER_H__
