#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Position.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableField /* listenable */ {

private:
    Sprite* sprite;
    std::vector<ViewEventListener*> listeners;
    void createSprite(int, int);

public:
    DrawableField(int, int);
    Sprite* getSprite();
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);
};

#endif // __DRAWABLEFIELD_H__
