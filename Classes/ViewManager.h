#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "ModelManager.h"
#include "DrawableBall.h"
#include "DrawableField.h"
#include "DrawableBar.h"
#include "ModelEventObserver.h"

USING_NS_CC;

class ViewManager : public ModelEventObserver {
private:    
    ModelManager mm;
    DrawableBall *dBall;
    DrawableField *dField;
    DrawableBar *dBar;
    void updateView();

public:
    void initialize(Scene* baseScene);
    void progress(float delta);
    void onUpdate();
};

#endif // __VIEWMANAGER_H__
