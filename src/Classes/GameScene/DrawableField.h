#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Position.h"
#include "Drawable.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableField : public Drawable {

private:
    Sprite* sprite;
    void createSprite(int, int);

public:
    DrawableField(int, int);
    Node* getNode();
};

#endif // __DRAWABLEFIELD_H__
