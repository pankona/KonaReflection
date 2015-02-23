#ifndef __DRAWABLEBAR_H__
#define __DRAWABLEBAR_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class DrawableBar {

private:    
    Sprite* sprite;
    void createSprite(int, int, Position);

public:
    DrawableBar(int, int, Position);
    Sprite* getSprite();
    void setPosition(Position);
};

#endif // __DRAWABLEBar_H__
