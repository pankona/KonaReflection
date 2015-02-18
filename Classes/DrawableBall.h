#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class DrawableBall {

private:    
    Ball* ball;
    DrawNode* drawNode;
    Sprite* sprite;
    void createDrawNode();
    void createSprite();

public:
    DrawableBall();
    Ball* getBall();
    DrawNode* getDrawNode();
    Sprite* getSprite();
    void updatePosition();
};

#endif // __DRAWABLEBALL_H__
