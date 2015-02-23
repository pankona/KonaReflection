#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "cocos2d.h"
#include "ViewManager.h"
#include "ModelManager.h"

USING_NS_CC;

class GameControl {
private:
    ModelManager mm;
    ViewManager  vm;

public:
    void initialize(Scene*);
    void update(float);
};

#endif // __FIELD_H__
