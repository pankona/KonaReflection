#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Field.h"

USING_NS_CC;

class DrawableField {

private:    
    Field* field;
    DrawNode* drawNode;
    void createDrawNode();
    void prepareOnTouchListener();

public:
    DrawableField(Field*);
    DrawNode* getDrawNode();

};

#endif // __DRAWABLEFIELD_H__
