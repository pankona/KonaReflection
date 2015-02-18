#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Field.h"

USING_NS_CC;

class DrawableField {

private:    
    Field* field;
    DrawNode* drawNode;
    Sprite* sprite;
    void createDrawNode();
    void createSprite();
    void prepareOnTouchListener();

public:
    DrawableField(Field*);
    DrawNode* getDrawNode();
    Sprite* getSprite();

};

#endif // __DRAWABLEFIELD_H__
