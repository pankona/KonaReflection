#ifndef __DRAWABLEBAR_H__
#define __DRAWABLEBAR_H__

#include "cocos2d.h"
#include "Bar.h"

USING_NS_CC;

class DrawableBar {

private:    
    Bar* bar;
    DrawNode* drawNode;

public:
    DrawableBar();
    Bar* getBar();

    void createDrawNode();
    DrawNode* getDrawNode();
};

#endif // __DRAWABLEBar_H__
