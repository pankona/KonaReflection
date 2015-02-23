#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Position.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableField {

private:
    Sprite* sprite;
    void createSprite(int, int);
    ViewEventListener* listener; // should be array

public:
    DrawableField(int, int);
    Sprite* getSprite();
    void addViewEventListener(ViewEventListener*);
    void ViewEventNotify(ViewEventListener::EventTag);
};

#endif // __DRAWABLEFIELD_H__
