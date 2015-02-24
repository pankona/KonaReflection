#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "cocos2d.h"
#include "ViewManager.h"
#include "ModelManager.h"
#include "ViewManagerEventListener.h"

USING_NS_CC;

class GameControl : public ViewManagerEventListener {
private:
    ModelManager mm;
    ViewManager  vm;

public:
    void initialize(Scene*);
    void update(float);
    void onViewManagerEvent(ViewManagerEventListener::ViewManagerEvent, void*);
};

#endif // __FIELD_H__
