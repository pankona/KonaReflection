#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class DrawableBall {

private:    
    Ball* ball;
    DrawNode* drawNode;
    void createDrawNode();

public:
    DrawableBall();
    Ball* getBall();
    DrawNode* getDrawNode();
    void updatePosition();
};

#endif // __DRAWABLEBALL_H__
