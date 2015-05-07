#ifndef __DRAWABLEBALL_H__
#define __DRAWABLEBALL_H__

#include "cocos2d.h"
#include "Position.h"
#include <string>

USING_NS_CC;

class DrawableBall {

private:    
    Sprite* sprite;
    int radius;
    void createSprite(int, Position, std::string);

public:
    DrawableBall(int, Position);
    DrawableBall(int, Position, std::string);
    Sprite* getSprite();
    void setPosition(Position);
    int getRadius();
};

#endif // __DRAWABLEBALL_H__
