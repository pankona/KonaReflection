#ifndef __DRAWABLEBAR_H__
#define __DRAWABLEBAR_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class DrawableBar {

private:    
    Sprite* sprite;
    void createSprite(int, int, Position);
    enum Pivot {
        LEFT,
        RIGHT,
        CENTER
    };
    Pivot currentPivot;
    int width;
    int height;

public:
    DrawableBar(int, int, Position);
    Sprite* getSprite();
    void setPosition(Position);

    void setPivotLeft();
    void setPivotRight();
    void setRotation(int);

    int getWidth();
};

#endif // __DRAWABLEBar_H__
