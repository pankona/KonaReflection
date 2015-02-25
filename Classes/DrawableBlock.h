#ifndef __DRAWABLEBLOCK_H__
#define __DRAWABLEBLOCK_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class DrawableBlock {

private:    
    Sprite* sprite;
    void createSprite(int, int, Position);

public:
    DrawableBlock(int, int, Position);
    Sprite* getSprite();
    void setPosition(Position);
};

#endif // __DRAWABLEBLOCK_H__
