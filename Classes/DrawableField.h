#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"

USING_NS_CC;

class DrawableField {

private:
    Sprite* sprite;
    void createSprite(int, int, Position);

public:
    DrawableField(int, int, Position);
    Sprite* getSprite();
    void setOnTouchCallback();
};

#endif // __DRAWABLEFIELD_H__
