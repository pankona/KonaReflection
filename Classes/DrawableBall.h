#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class DrawableBall {

private:    
    Sprite* sprite;
    void createSprite(int);

public:
    DrawableBall(int);
    Sprite* getSprite();
    void setPosition(Position);
};

#endif // __DRAWABLEBALL_H__
