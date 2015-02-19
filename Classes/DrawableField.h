#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Field.h"

USING_NS_CC;

class DrawableField {

private:    
    Field* field;
    Sprite* sprite;
    void createDrawNode();
    void createSprite();
    void prepareOnTouchListener();

public:
    DrawableField(Field*);
    Sprite* getSprite();
};

#endif // __DRAWABLEFIELD_H__
