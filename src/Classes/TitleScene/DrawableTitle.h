#ifndef __DRAWABLETITLE_H__
#define __DRAWABLETITLE_H__

#include "cocos2d.h"
#include "Drawable.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableTitle : public Drawable {

private:
    Sprite* sprite;
    void createSprite(int, int);

public:
    DrawableTitle(int, int);
    Node* getNode();
};

#endif // __DRAWABLETITLE_H__
