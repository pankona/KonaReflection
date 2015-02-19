#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class DrawableBall {

private:    
    Ball* ball;
    Sprite* sprite;
    void createDrawNode();
    void createSprite();

public:
    DrawableBall();
    Ball* getBall();
    Sprite* getSprite();
    void updatePosition();
};

#endif // __DRAWABLEBALL_H__
