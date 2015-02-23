#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"

USING_NS_CC;

class DrawableField {

private:
    Sprite* sprite;
    void createSprite(int, int);

public:
    DrawableField(int, int);
    Sprite* getSprite();
    void setOnTouchCallback();
};

#endif // __DRAWABLEFIELD_H__
