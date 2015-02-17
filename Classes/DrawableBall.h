#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class DrawableBall {

private:    
    Ball* ball;
    DrawNode* drawNode;

public:
    DrawableBall();

    void setBall(Ball*);
    Ball* getBall();

    void createDrawNode();
    DrawNode* getDrawNode();

    void updatePosition();
};

#endif // __DRAWABLEBALL_H__
