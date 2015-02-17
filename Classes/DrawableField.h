#ifndef __DRAWABLEFIELD_H__
#define __DRAWABLEFIELD_H__

#include "cocos2d.h"
#include "Field.h"

USING_NS_CC;

class DrawableField {

private:    
    Field* field;
    DrawNode* drawNode;

public:
    DrawableField(Field*);

    void createDrawNode();
    DrawNode* getDrawNode();
};

#endif // __DRAWABLEFIELD_H__
