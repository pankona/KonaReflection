#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "DrawableBall.h"
#include "DrawableField.h"
#include "DrawableBar.h"

USING_NS_CC;

class ViewManager {
private:    
    DrawableBall* dBall;
    DrawableField* dField;
    DrawableBar* dBar;

public:
    void initialize(Scene* baseScene);
    void updateView();
    void setBallPosition(Position);
    void setBarPosition(Position);
    void onTouchBegan(int, Event*, int, int);
    void onTouchMoved(int, Event*, int, int);
    void onTouchEnded(int, Event*);
};

#endif // __VIEWMANAGER_H__
