#ifndef __DRAWABLETITLE_H__
#define __DRAWABLETITLE_H__

#include "cocos2d.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableTitle /* listenable */ {

private:
    Sprite* sprite;
    std::vector<ViewEventListener*> listeners;
    void createSprite(int, int);

public:
    DrawableTitle(int, int);
    Sprite* getSprite();
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);
};

#endif // __DRAWABLETITLE_H__
