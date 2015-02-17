#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "cocos2d.h"
#include "ViewManager.h"

USING_NS_CC;

class GameControl {
private:
    ViewManager  vm;

public:
    void initialize(Scene*);
    void update(float);
};

#endif // __FIELD_H__
