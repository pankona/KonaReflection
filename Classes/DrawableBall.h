#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class DrawableBall : public cocos2d::DrawNode {

private:    
    Ball ball;
    DrawNode* drawNode;
public:
    void createDrawNode();
    DrawableBall();
    DrawableBall(Ball);
    void setBall(Ball);
    Ball* getBall();
    DrawNode* getDrawNode();
    void updatePosition();
};

#endif // __DRAWABLEBALL_H__
