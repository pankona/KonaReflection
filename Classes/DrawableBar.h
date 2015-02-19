#ifndef __DRAWABLEBAR_H__
#define __DRAWABLEBAR_H__

#include "cocos2d.h"
#include "Bar.h"

USING_NS_CC;

class DrawableBar {

private:    
    Bar* bar;
    Sprite* sprite;
    void createDrawNode();
    void createSprite();

public:
    DrawableBar();
    Bar* getBar();
    Sprite* getSprite();
    void updatePosition();
};

#endif // __DRAWABLEBar_H__
